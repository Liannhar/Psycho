// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/AttackComponent.h"
#include "BaseCharacter.h"
#include "BaseEnemy.h"
#include "BaseWeapon.h"
#include "WeaponComponent.h"
#include "CoreTypes.h"
#include "Kismet/GameplayStatics.h"

UAttackComponent::UAttackComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}

void UAttackComponent::StartAttack(EComboInput Input)
{
	for (int32 i=CurrentComboAttack; i < Combos.Num();i++ )
	{
		if(AttackIndex==0 || AttackIndex<Combos[i].TypeAttack.Num() && Combos[i].TypeAttack[AttackIndex]==Input && ( !CantAttackInTime|| CanAttackNext ))
		{
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
	
	WeaponComponent->EndAttack();
	AttackIndex=0;
	CurrentComboAttack=0;
	GetWorld()->GetTimerManager().ClearTimer(TimerEndAnimMontage);
}

void UAttackComponent::SetCombo()
{
	if (const auto Weapon =GetWeapon())
	{
		Combos = Weapon->DifferentCombos;
		for(auto Combo:Combos)
		{
			if(Combo.TypeAttack.Num()!=Combo.Attack.Num())
			{
				break;
			}
		}
	}
}

void UAttackComponent::ActiveAttack(FCombination Combo)
{
	const auto BaseCharacter = GetCharacter();
	if(!BaseCharacter) return;
	const auto TimeToEndAnimMontage = BaseCharacter->PlayAnimMontage(Combo.Attack[AttackIndex].AttackMontage,1);
	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(TimerEndAnimMontage,this,&UAttackComponent::EndAttack,TimeToEndAnimMontage,false);
	AttackIndex++;
}

/* проверить что forward vector сонаправлен с motionwarping
*/
void UAttackComponent::AttackTarget()
{
	/*if (const auto Enemy = ActionEnemy())
	{
		const auto Component = BaseCharacter->GetComponentByClass(UMotionWarpingComponent::StaticClass());
		if(!Component) return;
		const auto MotionWarpingComponent = Cast<UMotionWarpingComponent>(Component);
		if(!MotionWarpingComponent) return;
		
		const auto AttackLocation = Enemy->GetActorLocation();
		if (AttackLocation.IsZero()) return;
		
		const auto ForwardVector = BaseCharacter->GetActorForwardVector();

		UE_LOG(LogTemp,Display,TEXT("K%d"),FVector::Coincident(AttackLocation,ForwardVector)?1:0);
		UE_LOG(LogTemp,Display,TEXT("Z%d"),ForwardVector == AttackLocation ?1:0);
		UE_LOG(LogTemp,Display,TEXT("M%d"),ForwardVector.Equals(AttackLocation, 0.1f) ?1:0);
		//if(FVector::Coincident(AttackLocation.GetSafeNormal(),ForwardVector.GetSafeNormal()))
		//if(ForwardVector == AttackLocation)
		//if(ForwardVector.Equals(AttackLocation, 0.1f))
		//{
		FTransform AttackTransform;
		AttackTransform.SetLocation(AttackLocation);
		auto NewRotation = AttackLocation.Rotation();
		NewRotation.Pitch = 0.0f;
		AttackTransform.SetRotation(NewRotation.Quaternion());
		MotionWarpingComponent->AddOrUpdateWarpTargetFromTransform("Attack",AttackTransform);	
		//}
	}*/
}


void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

ABaseCharacter* UAttackComponent::GetCharacter() const
{
	const auto Actor = GetOwner();
	if(!Actor) return nullptr;

	const auto BaseCharacter = Cast<ABaseCharacter>(Actor);
	if(!BaseCharacter) return nullptr;

	return BaseCharacter;
}

ABaseWeapon* UAttackComponent::GetWeapon() const
{
	const auto BaseCharacter = GetCharacter();
	const auto Component = BaseCharacter->GetComponentByClass(UWeaponComponent::StaticClass());
	if(!Component) return nullptr;

	const auto WeaponComponent = Cast<UWeaponComponent>(Component);
	if(!WeaponComponent) return nullptr;

	return WeaponComponent->GetCurrentWeapon();
}

