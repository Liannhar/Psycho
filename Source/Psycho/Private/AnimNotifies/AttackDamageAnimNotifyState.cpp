// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\AnimNotifies\AttackDamageAnimNotifyState.h"

#include "ComponentsCoreTypes.h"

class UAttackComponent;


void UAttackDamageAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float FrameDeltaTime)
{
	if(const auto AttackComponent = GetAttackComponent(MeshComp))
	{
		AttackComponent->Damage();
	}
}

