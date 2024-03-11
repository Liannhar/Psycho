// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/AttackComponent.h"
#include "BaseCharacter.h"
#include "Player/PlayerCharacter.h"
#include "BaseEnemy.h"
#include "BaseEnemyAIController.h"
#include "BaseWeapon.h"
#include "WeaponComponent.h"
#include "CoreTypes.h"
#include "HealthComponent.h"
#include "MotionWarpingComponent.h"
#include "P_PlayerController.h"
#include "DamageType/AttackDamageType.h"
#include "Kismet/GameplayStatics.h"


UAttackComponent::UAttackComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}
//начинает атаку
void UAttackComponent::StartComboAttack(EComboInput Input)
{
	
	for (int32 i=CurrentComboAttack; i < Combos.Num();i++ )
	{
		if(AttackIndex<Combos[i].Attack.Num() && Combos[i].Attack[AttackIndex].TypeAttack==Input && (AttackIndex==0  || !CantAttackInTime || CanAttackNext ))
		{
			DamagedCharacters.Empty();
			IsLightAttackUse=false;
			CurrentComboInput=Combos[i].Attack[AttackIndex].TypeAttack;
			if(!CantAttackInTime)
			{
				if(Combos[i].Attack[AttackIndex].PreviosAttackNeedTiming)
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
	if (const auto& Weapon = WeaponComponent->GetCurrentWeapon())
	{
		Combos = Weapon->DifferentCombos;
	}
}

//Используется в AnimNotifyDamage для нанесения урона
void UAttackComponent::Damage()
{
	if(IsLightAttackUse)
	{
		return;
	}
	const auto ThisCharacter = GetCharacter();
	if(!ThisCharacter) return ;
	const auto BaseCharacter = Cast<ABaseCharacter>(ThisCharacter);
	if(!BaseCharacter) return;

	const UWeaponComponent* WeaponComponent = GetWeaponComponent();
	const auto Weapon = WeaponComponent->GetCurrentWeapon();
	if(!Weapon) return;

	bool IsEnemy = false;
	if(Cast<ABaseEnemy>(ThisCharacter)) IsEnemy=true;
	
	const auto SkeletalWeapon = Weapon->GetSkeletalMeshComponent();
	
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(ThisCharacter);
	FVector Start = FVector();
	FVector End = FVector();
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	if(IsEnemy)
	{
		Start = GetWeaponComponent()->GetCurrentWeapon()->GetActorLocation();
		End = GetWeaponComponent()->GetCurrentWeapon()->GetActorLocation()+ThisCharacter->GetActorForwardVector()*BaseCharacter->LengthLineAttack;
		ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	}
	else
	{
		int32 SignX = CompareSign(SkeletalWeapon->GetSocketLocation("EndAttack").X,SkeletalWeapon->GetSocketLocation("StartAttack").X);
		const auto SignY =CompareSign(SkeletalWeapon->GetSocketLocation("EndAttack").Y,SkeletalWeapon->GetSocketLocation("StartAttack").Y);
		Start=SkeletalWeapon->GetSocketLocation("StartAttack");
		End=FVector(SkeletalWeapon->GetSocketLocation("EndAttack").X+SignX*BaseCharacter->LengthLineAttack,SkeletalWeapon->GetSocketLocation("EndAttack").Y+SignY*BaseCharacter->LengthLineAttack,SkeletalWeapon->GetSocketLocation("EndAttack").Z);
		ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	}

	const auto Angle = GetAngle(BaseCharacter->GetActorRightVector(),End-Start);
	CurrentAttackDirection =CheckAngle(Angle);
	
	if(CurrentComboAttack<Combos.Num() && AttackIndex<Combos[CurrentComboAttack].Attack.Num())
		CurrentAttackRepulsion = Combos[CurrentComboAttack].Attack[AttackIndex].DamageDistance;
	
	switch (CurrentComboInput)
	{
	case None:
		break;
	case LightAttack:
		{
			FHitResult HitResult;
			if(UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, SphereDamageRadius, ObjectTypesArray, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true))
			{
				IsLightAttackUse=true;
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
				
					if(IsEnemy && (Cast<ABaseEnemy>(DamagedCharacter) || DamagedCharacter->GetAttackComponent()->GetIsDodge()))
					{
						return ;
					}
					if(NextHitResult)
					{
						break;
					}

					
					ChooseNewCurrentTheNearestDamagedCharacter(DamagedCharacter,ThisCharacter);
					
					if(IsEnemy && Cast<ABaseEnemy>(DamagedCharacter))
					{
						return ;
					}
					UGameplayStatics::ApplyDamage(DamagedCharacter,
						Weapon->GetLightAttackDamage()* AttackDamage,
						ThisCharacter->GetController(),
						ThisCharacter,UAttackDamageType::StaticClass());
				}
			}
			break;
		}
	case HeavyAttack:
		{
			TArray<FHitResult> HitResults;
			if(UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, SphereDamageRadius, ObjectTypesArray, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true))
			{
				for(auto NewHitResult:HitResults)
				{
					auto HitActor = NewHitResult.GetActor();
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
						
						UGameplayStatics::ApplyDamage(DamagedCharacter,
							Weapon->GetHeavyAttackDamage()* AttackDamage,
							ThisCharacter->GetController(),
							ThisCharacter,
							UAttackDamageType::StaticClass());
					}
				}
			}
			break;	
		}
	}
}

void UAttackComponent::ChooseNewCurrentTheNearestDamagedCharacter(ABaseCharacter*& DamagedCharacter, const ABaseCharacter* ThisCharacter)
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
void UAttackComponent::ActiveAttack(FCombination& Combo)
{
	const auto ThisCharacter = GetCharacter();
	if(!ThisCharacter) return;
	AttackTarget();
	TimeToEndCurrentAnimMontage = ThisCharacter->PlayAnimMontage(Combo.Attack[AttackIndex].AttackMontage,AttackSpeed);
	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(TimerEndAnimMontage,this,&UAttackComponent::EndAttackCombo,TimeToEndCurrentAnimMontage,false);
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
	if(!PlayerController)
	{
		const auto EnemyController = Cast<ABaseEnemyAIController>(Controller); 
		if(!EnemyController) return;
		
		MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation("Attack",EnemyController->GetPlayerCharacter()->GetActorLocation());
	}
	
	FTransform AttackTransform=ThisCharacter->GetActorTransform();
	if(!PlayerController->GetLockOnTarget())
	{
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
	}
	MotionWarpingComponent->AddOrUpdateWarpTargetFromTransform("Attack",AttackTransform);
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


FRotator UAttackComponent::CheckRotationWithAttack(const ABaseCharacter* DamagedActor, const ABaseCharacter* ThisCharacter,FRotator& Rotation)
{
	if(!DamagedActor || DamagedActor->GetHealthComponent()->IsDead())
	{
		return FRotator().ZeroRotator;
	}
	FVector Direction1To2 = DamagedActor->GetActorLocation() - ThisCharacter->GetActorLocation();
	Direction1To2.Normalize();
	const FVector Forward1 = FRotationMatrix(Rotation).GetUnitAxis(EAxis::X);
	const float DistanceBetweenActors = FVector::Distance(ThisCharacter->GetActorLocation(),DamagedActor->GetActorLocation());
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
		IsDodge=false;
			
		GetWorld()->GetTimerManager().ClearTimer(DodgeTimer);
	}
}

void UAttackComponent::SideDodge()
{
	if(DodgeTimer.IsValid()) return;	
	
	auto ThisCharacter = GetCharacter();
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
	IsDodge=true;
	IdealDodgeCheck(ThisCharacter);
}

void UAttackComponent::CommonDodge()
{
	if(DodgeTimer.IsValid()) return;	
	
	auto ThisCharacter = GetCharacter();
	if(!ThisCharacter) return ;
	
	if(!GetWorld()) return;

	const auto Controller = Cast<AP_PlayerController>(ThisCharacter->GetController());
	if(!Controller) return;
	
	if (UAnimInstance* AnimInstance = ThisCharacter->GetMesh()->GetAnimInstance())
	{
		AnimInstance->Montage_Stop(0.0f);
	}
	EndAttackCombo();
	const FRotator NewRotation = ThisCharacter->GetActorRotation() + FRotator(0.0f, RotationAngle(ThisCharacter)*RotationSpeed, 0.0f);
	const float YawInRadians = FMath::DegreesToRadians(NewRotation.Yaw);
	const FVector Direction = FVector(FMath::Cos(YawInRadians), FMath::Sin(YawInRadians), 0.0f).GetSafeNormal();
	
	const auto Component = ThisCharacter->GetComponentByClass(UMotionWarpingComponent::StaticClass());
	if(!Component) return;
	const auto MotionWarpingComponent = Cast<UMotionWarpingComponent>(Component);
	if(!MotionWarpingComponent) return;
	const auto Player = Cast<APlayerCharacter>(ThisCharacter);
	if(!Player) return;
	
	const auto NewLocation = ThisCharacter->GetActorLocation()+Direction* LengthOfDodge;

	auto NewTransform = FTransform();
	NewTransform.SetLocation(NewLocation);
	ThisCharacter->SetActorRotation(NewRotation);
	NewTransform.SetRotation(ThisCharacter->GetActorRotation().Quaternion());

	MotionWarpingComponent->AddOrUpdateWarpTargetFromTransform("Dodge",NewTransform);

	IsDodge=true;
	
	const auto TimeDodge = Player->PlayAnimMontage(Player->DodgeForward);
	GetWorld()->GetTimerManager().SetTimer( DodgeTimer, this,&UAttackComponent::EndDodge, TimeDodge,false);	
	IdealDodgeCheck(ThisCharacter);
}

float UAttackComponent::GetAngle(const FVector& RightVector, const FVector& AnotherVector)
{
	return FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(RightVector, AnotherVector.GetSafeNormal())));
}

int32 UAttackComponent::CheckAngle(const float& Angle)
{
	return (Angle > 95.0f) ? 1 : ((Angle<85.0f) ? -1 : 0);
}

void UAttackComponent::IdealDodgeCheck(ABaseCharacter*& ThisCharacter) const
{
	const FVector Start = ThisCharacter->GetActorLocation();
	const FVector End = Start;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(ThisCharacter);
	TArray<FHitResult> HitResults;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));
	UE_LOG(LogTemp,Display,TEXT("KKKKK"));
	if (UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, CheckDodgeRadius, ObjectTypesArray, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true))
	{
		for(auto& HitResult:HitResults)
		{
			if (ABaseEnemy* EnemyCharacter = Cast<ABaseEnemy>(HitResult.GetActor()))
			{
				if(EnemyCharacter->GetIdealDodge())
				{
					EnemyCharacter->StunEnemy(10.0f);
				}
			}
		}
	}
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

