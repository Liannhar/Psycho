// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/AI/BaseEnemyAIController.h"
#include "FirstBossAIController.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API AFirstBossAIController : public ABaseEnemyAIController
{
	GENERATED_BODY()
public:
	void SetBoolCurrentStamina(const int32& CurrentStamina);
protected:
	virtual bool GetCanFocus() const override;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="AI")
	FName IsStaminaNotOut = "IsStaminaNotOut";
	virtual void OnPossess(APawn* InPawn) override;
};
