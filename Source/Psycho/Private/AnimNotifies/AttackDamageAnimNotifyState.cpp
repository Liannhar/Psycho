// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\AnimNotifies\AttackDamageAnimNotifyState.h"

#include "BaseCharacter.h"

class UAttackComponent;


void UAttackDamageAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	if(const auto AttackComponent = GetAttackComponent(MeshComp))
	{
		AttackComponent->Damage();
	}
}

//получаем AttackComponent с персонажа, вызвавшего DamageNotify
UAttackComponent* UAttackDamageAnimNotifyState::GetAttackComponent(USkeletalMeshComponent* MeshComp)
{
	const auto Actor = MeshComp->GetOwner();
	if(!Actor) return nullptr;
	const auto BaseCharacter = Cast<ABaseCharacter>(Actor);
	if(!BaseCharacter) return nullptr;
	const auto Component = BaseCharacter->GetComponentByClass(UAttackComponent::StaticClass());
	if(!Component) return nullptr;
	const auto AttackComponent = Cast<UAttackComponent>(Component);
	if(!AttackComponent) return nullptr;
	
	return AttackComponent;
}
