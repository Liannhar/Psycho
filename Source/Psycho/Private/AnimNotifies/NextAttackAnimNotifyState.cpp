// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/NextAttackAnimNotifyState.h"

#include "AttackComponent.h"
#include "BaseCharacter.h"
#include "ComponentsCoreTypes.h"

UNextAttackAnimNotifyState::UNextAttackAnimNotifyState()
{
	
}
//при прохождение начальной точки NotifyState выставляем bool в true, что теперь можно попасть в тайминг атаки
void UNextAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                             float TotalDuration)
{
	if(const auto AttackComponent = GetAttackComponent(MeshComp))
	{
		AttackComponent->SetNextAttack(true);
	}
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
}
//при прохождение конечной точки NotifyState выставляем bool в false, что  тайминг атаки закончился
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

