// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackDamageAnimNotifyState.generated.h"

/**
 * Notify который отвечает за момент нанесения урона.
 */
UCLASS()
class PSYCHO_API UAttackDamageAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
protected:
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
};
