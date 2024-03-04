// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "FirstBossDeathAnimNotify.generated.h"

class AFirstBossEnemy;
class UWeaponComponent;
/**
 * 
 */
UCLASS()
class PSYCHO_API UFirstBossDeathAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
