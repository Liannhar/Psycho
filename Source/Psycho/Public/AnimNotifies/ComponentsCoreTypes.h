#pragma once
#include "AttackComponent.h"
#include "BaseCharacter.h"


//получаем AttackComponent с персонажа, вызвавшего DamageNotify
inline UAttackComponent* GetAttackComponent(USkeletalMeshComponent*& MeshComp)
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