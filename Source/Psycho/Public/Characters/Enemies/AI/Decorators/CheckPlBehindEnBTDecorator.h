// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CheckPlBehindEnBTDecorator.generated.h"


class ABaseEnemy;

UCLASS()
class PSYCHO_API UCheckPlBehindEnBTDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
	UCheckPlBehindEnBTDecorator();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector PlayerKey;
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	static bool CheckPlayerBehindEnemy(const ABaseEnemy* Enemy, const AActor* Player);
};
