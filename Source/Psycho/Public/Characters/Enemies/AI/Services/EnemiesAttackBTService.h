// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "EnemiesAttackBTService.generated.h"

/**
 * Service that checks if another enemy is attacking now
 */
UCLASS()
class PSYCHO_API UEnemiesAttackBTService : public UBTService
{
	GENERATED_BODY()
public:
	UEnemiesAttackBTService();
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector EnemyIsAttackingKey;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	float SlowSpeed=200.0f;
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
