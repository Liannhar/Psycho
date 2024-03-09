// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "IdealDodgeAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UIdealDodgeAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload) override;
	virtual void BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload) override;
};
