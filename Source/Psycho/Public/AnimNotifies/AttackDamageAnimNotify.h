// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttackComponent.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AttackDamageAnimNotify.generated.h"

/**
 * Notify который отвечает за момент нанесения урона.
 */
UCLASS()
class PSYCHO_API UAttackDamageAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
protected:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	UAttackComponent* GetAttackComponent(USkeletalMeshComponent* MeshComp);
};
