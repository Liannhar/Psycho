// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "NextAttackAnimNotifyState.generated.h"

class UAttackComponent;
/**
 * NextAttack Anim Notify отвечает за продвинуту. кобинацию атаки комбинацию атаки
 */
UCLASS()
class PSYCHO_API UNextAttackAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UNextAttackAnimNotifyState();
protected:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime) override;
	UAttackComponent* GetAttackComponent(USkeletalMeshComponent* MeshComp);
};
