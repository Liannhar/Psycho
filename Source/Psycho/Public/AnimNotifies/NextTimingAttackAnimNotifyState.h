// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NextTimingAttackAnimNotifyState.generated.h"

class UAttackComponent;
/**
 *  TimeOfAttack Anim Notify State отвечает за тайминг обысной кобинации атак
 */
UCLASS()
class PSYCHO_API UNextTimingAttackAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UNextTimingAttackAnimNotifyState();
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	UAttackComponent* GetAttackComponent(USkeletalMeshComponent* MeshComp);
};
