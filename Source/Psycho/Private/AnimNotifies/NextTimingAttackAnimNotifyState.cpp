// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/NextTimingAttackAnimNotifyState.h"

#include "AttackComponent.h"
#include "BaseCharacter.h"
#include "ComponentsCoreTypes.h"

UNextTimingAttackAnimNotifyState::UNextTimingAttackAnimNotifyState()
{
}
//при прохождение начальной точки NotifyState выставляем bool в true, что теперь можно попасть в тайминг атаки
void UNextTimingAttackAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if(const auto AttackComponent = GetAttackComponent(MeshComp))
	{
		AttackComponent->SetTimeAttack(false);
	}
}

//при прохождение конечной точки NotifyState выставляем bool в false, что  тайминг атаки закончился
void UNextTimingAttackAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if(const auto AttackComponent = GetAttackComponent(MeshComp))
	{
		AttackComponent->SetTimeAttack(true);
	}
}

void UNextTimingAttackAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	
}
