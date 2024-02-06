// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/AttackComponent.h"
#include "BaseCharacter.h"
#include "Player/PlayerCharacter.h"
#include "BaseEnemy.h"
#include "BaseWeapon.h"
#include "WeaponComponent.h"
#include "CoreTypes.h"
#include "HealthComponent.h"
#include "MotionWarpingComponent.h"
#include "P_PlayerController.h"
#include "DamageType/HeavyAttackDamageType.h"
#include "Kismet/GameplayStatics.h"

UAttackComponent::UAttackComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}
//начинает атаку
void UAttackComponent::StartComboAttack(EComboInput Input)
{
	DamagedCharacters.Empty();
	for (int32 i=CurrentComboAttack; i < Combos.Num();i++ )
	{
		if(AttackIndex<Combos[i].Attack.Num() && Combos[i].Attack[AttackIndex].TypeAttack==Input && (AttackIndex==0  || !CantAttackInTime || CanAttackNext ))
		{
			CurrentComboInput=Combos[i].Attack[AttackIndex].TypeAttack;
			if(Combos[i].Attack[AttackIndex].PreviosAttackNeedTiming)
			{
				if( CanAttackNext )
				{
					CurrentComboAttack=i;
					ActiveAttack(Combos[i]);	
					break;	
				}
				continue;
			}

			CurrentComboAttack=i;
			ActiveAttack(Combos[i]);
			break;
		}
	}
}

void UAttackComponent::EndAttackCombo()
{
	const auto BaseCharacter = GetCharacter();
	const auto Component = BaseCharacter->GetComponentByClass(UWeaponComponent::StaticClass());
	if(!Component) return;
	
	const auto WeaponComponent = Cast<UWeaponComponent>(Component);
	if(!WeaponComponent) return;
	
	AttackIndex=0;
	CurrentComboAttack=0;
	CurrentComboInput=None;
	CurrentTheNearestDamagedCharacter=nullptr;
	GetWorld()->GetTimerManager().ClearTimer(TimerEndAnimMontage);
}



void UAttackComponent::SetCombo()
{
	const UWeaponComponent* WeaponComponent = GetWeaponComponent();
	if (const auto Weapon = WeaponComponent->GetCurrentWeapon())
	{
		Combos = Weapon->DifferentCombos;
	}
}

//Используется в AnimNotifyDamage для нанесения урона
void UAttackComponent::Damage()
{
	const auto ThisCharacter = GetCharacter();
	if(!ThisCharacter) return ;
	const auto BaseCharacter = Cast<ABaseCharacter>(ThisCharacter);
	if(!BaseCharacter) return;

	TArray<FHitResult> HitResults;
	FVector Start = GetWeaponComponent()->GetCurrentWeapon()->GetActorLocation();
	FVector End = GetWeaponComponent()->GetCurrentWeapon()->GetActorLocation()+ThisCharacter->GetActorForwardVector()*BaseCharacter->LengthLineAttack;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(ThisCharacter);
	bool IsEnemy = false;
	if(Cast<ABaseEnemy>(ThisCharacter)) IsEnemy=true;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	if(IsEnemy)
	{
		ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	}
	else
	{
		ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));
	}

	
	if(UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, SphereDamageRadius, ObjectTypesArray, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true))
	{
		for(auto HitResult:HitResults)
		{
			auto HitActor = HitResult.GetActor();
			if(auto DamagedCharacter = Cast<ABaseCharacter>(HitActor))
			{
				bool NextHitResult=false;
				for(auto DamageChar:DamagedCharacters)
				{
					if(DamagedCharacter->GetName()==DamageChar->GetName())
					{
						NextHitResult=true;
						break;
					}
				}
				
				if(IsEnemy && Cast<ABaseEnemy>(DamagedCharacter))
				{
					return ;
				}
				if(NextHitResult)
				{
					continue;
				}

				ChooseNewCurrentTheNearestDamagedCharacter(DamagedCharacter,ThisCharacter);
				const UWeaponComponent* WeaponComponent = GetWeaponComponent();
				const auto Weapon = WeaponComponent->GetCurrentWeapon();
				switch (CurrentComboInput)
				{
				case None:
					break;
				case LightAttack:
					UGameplayStatics::ApplyDamage(DamagedCharacter,
						Weapon->GetLightAttackDamage()* AttackDamage,
						ThisCharacter->GetController(),
						ThisCharacter,
						UDamageType::StaticClass());
					break;
				case HeavyAttack:
					UGameplayStatics::ApplyDamage(DamagedCharacter,
						Weapon->GetHeavyAttackDamage()* AttackDamage,
						ThisCharacter->GetController(),
						ThisCharacter,
						UHeavyAttackDamageType::StaticClass());
					break;
				}
			
			}
		}
	}
}

void UAttackComponent::ChooseNewCurrentTheNearestDamagedCharacter(ABaseCharacter* DamagedCharacter, const ABaseCharacter* ThisCharacter)
{
	DamagedCharacters.Add(DamagedCharacter);
	FVector Direction1To2 = DamagedCharacter->GetActorLocation() - ThisCharacter->GetActorLocation();
	Direction1To2.Normalize();

	const FVector Forward1 = ThisCharacter->GetActorForwardVector();

	if (FVector::DotProduct(Forward1, Direction1To2)> 0.0f)
	{
		if(!CurrentTheNearestDamagedCharacter)
		{
			CurrentTheNearestDamagedCharacter=DamagedCharacter;
		}
		else
		{
			const auto CurrentDistance = FVector::Distance(CurrentTheNearestDamagedCharacter->GetActorLocation(),ThisCharacter->GetActorLocation());
			const auto CurrentNewDistance = FVector::Distance(DamagedCharacter->GetActorLocation(),ThisCharacter->GetActorLocation());
			if(CurrentDistance>CurrentNewDistance)
			{
				CurrentTheNearestDamagedCharacter=DamagedCharacter;
			}
		}	
	}
	
}

/*
 * использует AnimMontage и ставит таймер по истечению которого закончит атаку.
 */
void UAttackComponent::ActiveAttack(FCombination Combo)
{
	const auto ThisCharacter = GetCharacter();
	if(!ThisCharacter) return;
	AttackTarget();
	const auto TimeToEndAnimMontage = ThisCharacter->PlayAnimMontage(Combo.Attack[AttackIndex].AttackMontage,AttackSpeed);
	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(TimerEndAnimMontage,this,&UAttackComponent::EndAttackCombo,TimeToEndAnimMontage,false);
	AttackIndex++;
}

/*
 *использует motion warping чтобы передать в него новую позицию и поворот для атаки
*/
void UAttackComponent::AttackTarget() const
{
	const auto ThisCharacter = GetCharacter();
	if(!ThisCharacter) return;

	if (!Cast<APlayerCharacter>(ThisCharacter)) return;
	const auto Component = ThisCharacter->GetComponentByClass(UMotionWarpingComponent::StaticClass());
	if(!Component) return;
	const auto MotionWarpingComponent = Cast<UMotionWarpingComponent>(Component);
	if(!MotionWarpingComponent) return;
	
	const auto Controller = ThisCharacter->GetController();
	if(!Controller) return;		
	const auto PlayerController = Cast<AP_PlayerController>(Controller);
	if(!PlayerController) return;


	UE_LOG(LogTemp,Display,TEXT("A %d"),!PlayerController->GetLockOnTarget()?1:0);
	
	if(!PlayerController->GetLockOnTarget())
	{
		FTransform AttackTransform;
		auto NewRotation = ThisCharacter->GetActorRotation();
		NewRotation	+=FRotator(0.0f,RotationAngle(ThisCharacter)*RotationSpeed,0.0f);
		if(const auto EnemyRotation = CheckRotationWithAttack(CurrentTheNearestDamagedCharacter,ThisCharacter,NewRotation);!EnemyRotation.IsZero())
		{
			AttackTransform.SetLocation(ThisCharacter->GetActorLocation());
			AttackTransform.SetRotation(EnemyRotation.Quaternion());
		}
		else
		{
			AttackTransform.SetLocation(ThisCharacter->GetActorLocation());
			AttackTransform.SetRotation(NewRotation.Quaternion());
		}
		MotionWarpingComponent->AddOrUpdateWarpTargetFromTransform("Attack",AttackTransform);
	}
}

void UAttackComponent::MultiplyAttackSpeed(const float& Multiplier)
{
	AttackSpeed *= Multiplier;
	GetCharacter()->GetMesh()->GetAnimInstance()->Montage_SetPlayRate(Combos[CurrentComboAttack].Attack[AttackIndex].AttackMontage);
}


void UAttackComponent::ResetAttackSpeedToDefault()
{
	AttackSpeed = 1.f;
	if (CurrentComboAttack < Combos.Num() && AttackIndex < Combos[CurrentComboAttack].Attack.Num())
		GetCharacter()->GetMesh()->GetAnimInstance()->Montage_SetPlayRate(Combos[CurrentComboAttack].Attack[AttackIndex].AttackMontage);
}


FRotator UAttackComponent::CheckRotationWithAttack(const ABaseCharacter* DamagedActor, const ABaseCharacter* ThisCharacter,FRotator Rotation)
{
	if(!DamagedActor || DamagedActor->GetHealthComponent()->IsDead())
	{
		return FRotator().ZeroRotator;
	}
	FVector Direction1To2 = DamagedActor->GetActorLocation() - ThisCharacter->GetActorLocation();
	Direction1To2.Normalize();
	FVector Forward1 = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
	float DistanceBetweenActors = FVector::Distance(ThisCharacter->GetActorLocation(),DamagedActor->GetActorLocation());
	if ((FVector::DotProduct(Forward1, Direction1To2) > 0.0f) && (DistanceBetweenActors<100.0f) )
	{
		return Direction1To2.Rotation();
	}
	return FRotator().ZeroRotator;
}

void UAttackComponent::EndDodge()
{
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(DodgeTimer);
	}
}

void UAttackComponent::EndSprintDodge()
{
	if(!GetWorld()) return;
	const auto ThisCharacter = GetCharacter();
	if(!ThisCharacter) return ;
	
	if(!GetWorld()) return;

	const auto Controller = Cast<AP_PlayerController>(ThisCharacter->GetController());
	if(!Controller) return;

	Controller->StopSprint(Value);
		
	GetWorld()->GetTimerManager().ClearTimer(DodgeTimer);
	
}

void UAttackComponent::Dodge()
{
	if(DodgeTimer.IsValid()) return;	
	
	const auto ThisCharacter = GetCharacter();
	if(!ThisCharacter) return ;
	const auto RotationDodge = RotationAngle(ThisCharacter);
	const auto PlayerCharacter = Cast<APlayerCharacter>(ThisCharacter);
	if(!PlayerCharacter) return;
	if(!GetWorld()) return;
	
	if(RotationDodge>0.0f)
	{
		const auto TimeDodge = PlayerCharacter->PlayAnimMontage(PlayerCharacter->DodgeRight,1.5f);
		GetWorld()->GetTimerManager().SetTimer(DodgeTimer,this,&UAttackComponent::EndDodge,TimeDodge);
	}
	else
	{
		const auto TimeDodge = PlayerCharacter->PlayAnimMontage(PlayerCharacter->DodgeLeft,1.5f);
		GetWorld()->GetTimerManager().SetTimer(DodgeTimer,this,&UAttackComponent::EndDodge,TimeDodge);
	}
}

void UAttackComponent::SprintDodge(const FInputActionValue& NewValue)
{
	if(DodgeTimer.IsValid()) return;	
	
	const auto ThisCharacter = GetCharacter();
	if(!ThisCharacter) return ;
	
	if(!GetWorld()) return;

	const auto Controller = Cast<AP_PlayerController>(ThisCharacter->GetController());
	if(!Controller) return;

	

	if (UAnimInstance* AnimInstance = ThisCharacter->GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Stop(0.0f);
	}
	
	
	Value = NewValue;
	Controller->DodgeSprint(Value);
	GetWorld()->GetTimerManager().SetTimer( DodgeTimer, this,&UAttackComponent::EndSprintDodge, 0.5f,false);	
}


float UAttackComponent::RotationAngle(const ABaseCharacter* BaseCharacter) const
{
	
	const FVector CurrentDirection = FVector(FVector2D(BaseCharacter->GetActorForwardVector()), 0.0f).GetSafeNormal2D();

	const FVector2D TargetForwardVector = FVector2D(ForwardDirection).GetSafeNormal();
	const FVector2D TargetRightVector = FVector2D(RightDirection).GetSafeNormal();

	const FVector WorldTargetDirection = FVector(
		TargetForwardVector * AttackDirection.Y + TargetRightVector * AttackDirection.X, 0.0f).GetSafeNormal2D();

	const float Sign = FMath::Sign(FVector::CrossProduct(CurrentDirection, WorldTargetDirection).Z);
	const float DeltaAngle = Sign * FMath::Acos(FVector::DotProduct(WorldTargetDirection, CurrentDirection));
	return DeltaAngle;
}




void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}

ABaseCharacter* UAttackComponent::GetCharacter() const
{
	const auto Actor = GetOwner();
	if(!Actor) return nullptr;

	const auto BaseCharacter = Cast<ABaseCharacter>(Actor);
	if(!BaseCharacter) return nullptr;

	return BaseCharacter;
}

UWeaponComponent* UAttackComponent::GetWeaponComponent() const
{
	const auto BaseCharacter = GetCharacter();
	const auto Component = BaseCharacter->GetComponentByClass(UWeaponComponent::StaticClass());
	if(!Component) return nullptr;

	const auto WeaponComponent = Cast<UWeaponComponent>(Component);
	if(!WeaponComponent) return nullptr;

	return WeaponComponent;
}

