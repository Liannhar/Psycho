// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/NextAttackAnimNotifyState.h"

#include "AttackComponent.h"
#include "BaseCharacter.h"

UNextAttackAnimNotifyState::UNextAttackAnimNotifyState()
{
	
}

void UNextAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             float TotalDuration)
{
	if(const auto AttackComponent = GetAttackComponent(MeshComp))
	{
		AttackComponent->SetNextAttack(true);
	}
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
}

void UNextAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(const auto AttackComponent = GetAttackComponent(MeshComp))
	{
		AttackComponent->SetNextAttack(false);
	}
	Super::NotifyEnd(MeshComp, Animation);
}

void UNextAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
}

UAttackComponent* UNextAttackAnimNotifyState::GetAttackComponent(USkeletalMeshComponent* MeshComp)
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

