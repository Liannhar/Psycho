// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CheckProcentHPBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UCheckProcentHPBTDecorator : public UBTDecorator
{
	GENERATED_BODY()
	UCheckProcentHPBTDecorator();
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere,Category="HP")
	float MinValue=0.0f;
	UPROPERTY(EditAnywhere,Category="HP")
	float MaxValue=100.f;
};
