// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/TimeOfAttackAnimNotifyState.h"

#include "AttackComponent.h"
#include "BaseCharacter.h"

UTimeOfAttackAnimNotifyState::UTimeOfAttackAnimNotifyState()
{
}
//при прохождение начальной точки NotifyState выставляем bool в true, что теперь можно попасть в тайминг атаки
void UTimeOfAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if(const auto AttackComponent = GetAttackComponent(MeshComp))
	{
		AttackComponent->SetTimeAttack(false);
	}
}

//при прохождение конечной точки NotifyState выставляем bool в false, что  тайминг атаки закончился
void UTimeOfAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if(const auto AttackComponent = GetAttackComponent(MeshComp))
	{
		AttackComponent->SetTimeAttack(true);
	}
}

void UTimeOfAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	
}

//получаем AttackComponent
UAttackComponent* UTimeOfAttackAnimNotifyState::GetAttackComponent(USkeletalMeshComponent* MeshComp)
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
