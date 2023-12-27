// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "EnemyDamagedBTService.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UEnemyDamagedBTService : public UBTService
{
	GENERATED_BODY()
public:
	UEnemyDamagedBTService();
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	FBlackboardKeySelector EnemyIsDamagedKey;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI",meta=(ClampMin=0.0f,ClampMax=1.0f))
	float Probability=0.8f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="AI")
	float TimePerBlock=5.0f;
	FTimerHandle ProbabilityTimerHandle;
	void CanBeDamaged();
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
