// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/AttackComponent.h"
#include "BaseCharacter.h"
#include "Player/PlayerCharacter.h"
#include "BaseEnemy.h"
#include "BaseWeapon.h"
#include "WeaponComponent.h"
#include "CoreTypes.h"
#include "MotionWarpingComponent.h"
#include "P_PlayerController.h"
#include "DamageType/HeavyAttackDamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"

UAttackComponent::UAttackComponent()
{

	PrimaryComponentTick.bCanEverTick = false;
}
//начинает атаку
void UAttackComponent::StartAttack(EComboInput Input)
{
	for (int32 i=CurrentComboAttack; i < Combos.Num();i++ )
	{
		if(AttackIndex<Combos[i].Attack.Num() && Combos[i].Attack[AttackIndex].TypeAttack==Input && (AttackIndex==0  || !CantAttackInTime|| CanAttackNext ))
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

void UAttackComponent::EndAttack()
{
	const auto BaseCharacter = GetCharacter();
	const auto Component = BaseCharacter->GetComponentByClass(UWeaponComponent::StaticClass());
	if(!Component) return;
	
	const auto WeaponComponent = Cast<UWeaponComponent>(Component);
	if(!WeaponComponent) return;
	
	AttackIndex=0;
	CurrentComboAttack=0;
	CurrentComboInput=None;
	GetWorld()->GetTimerManager().ClearTimer(TimerEndAnimMontage);
}

void UAttackComponent::SetCombo()
{
	const UWeaponComponent* WeaponComponent = GetWeaponComponent();
	const auto Weapon = WeaponComponent->GetCurrentWeapon();
	if (Weapon)
	{
		Combos = Weapon->DifferentCombos;
	}
}

//Используется в AnimNotifyDamage для нанесения урона
void UAttackComponent::Damage() const
{
	const auto BaseCharacter = GetCharacter();
	if(!BaseCharacter) return;

	FHitResult HitResult;
	FVector Start = BaseCharacter->GetActorLocation();
	FVector End = BaseCharacter->GetActorLocation()+BaseCharacter->GetActorForwardVector()*LengthLineAttack;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(BaseCharacter);
	bool IsEnemy = false;
	if(Cast<ABaseEnemy>(BaseCharacter)) IsEnemy=true;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECC_Pawn));
	
	if(UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, SphereDamageRadius, ObjectTypesArray, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true))
	{
		const auto HitActor = HitResult.GetActor();
		
		if(const auto Enemy = Cast<ABaseCharacter>(HitActor))
		{
			if(IsEnemy && Cast<ABaseEnemy>(Enemy))
			{
				return;
			}
			const UWeaponComponent* WeaponComponent = GetWeaponComponent();
			const auto Weapon = WeaponComponent->GetCurrentWeapon();
			switch (CurrentComboInput)
			{
				case None:
					break;
			    case LightAttack:
					UGameplayStatics::ApplyDamage(Enemy,
						Weapon->GetLightAttackDamage(),
						BaseCharacter->GetController(),
						BaseCharacter,
						UDamageType::StaticClass());
					break;
				case HeavyAttack:
					UGameplayStatics::ApplyDamage(Enemy,
						Weapon->GetHeavyAttackDamage(),
						BaseCharacter->GetController(),
						BaseCharacter,
						UHeavyAttackDamageType::StaticClass());
					break;
			}
			
		}
	}
}
/*
 * использует AnimMontage и ставит таймер по истечению которого закончит атаку.
 */
void UAttackComponent::ActiveAttack(FCombination Combo)
{
	const auto BaseCharacter = GetCharacter();
	if(!BaseCharacter) return;
	AttackTarget();
	const auto TimeToEndAnimMontage = BaseCharacter->PlayAnimMontage(Combo.Attack[AttackIndex].AttackMontage,1);
	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(TimerEndAnimMontage,this,&UAttackComponent::EndAttack,TimeToEndAnimMontage,false);
	AttackIndex++;
}

/*
 *использует motion warping чтобы передать в него новую позицию и поворот для атаки
*/
void UAttackComponent::AttackTarget() const
{
	const auto BaseCharacter = GetCharacter();
	if(!BaseCharacter) return;

	if (!Cast<APlayerCharacter>(BaseCharacter)) return;
	const auto Component = BaseCharacter->GetComponentByClass(UMotionWarpingComponent::StaticClass());
	if(!Component) return;
	const auto MotionWarpingComponent = Cast<UMotionWarpingComponent>(Component);
	if(!MotionWarpingComponent) return;
	
	const auto Controller = BaseCharacter->GetController();
	if(!Controller) return;
	const auto PlayerController = Cast<AP_PlayerController>(Controller);
	if(!PlayerController) return;

	FTransform AttackTransform;
	if(PlayerController->GetLockOnTarget())
	{
		AttackTransform.SetLocation(PlayerController->GetLockedOnTarget()->GetActorLocation());
		AttackTransform.SetRotation(BaseCharacter->GetActorRotation().Quaternion());
	}
	else
	{
		AttackTransform.SetLocation(BaseCharacter->GetActorLocation());
		auto NewRotation = BaseCharacter->GetActorRotation();
		NewRotation	+=FRotator(0.0f,RotationAngle(BaseCharacter)*RotationSpeed,0.0f);
		
		AttackTransform.SetRotation(NewRotation.Quaternion());
		MotionWarpingComponent->AddOrUpdateWarpTargetFromTransform("Attack",AttackTransform);
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

