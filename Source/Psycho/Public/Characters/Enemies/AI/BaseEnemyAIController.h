// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyAIController.generated.h"

class UEnemyAIPerceptionComponent;
/**
 * AI Controller
 */
UCLASS()
class PSYCHO_API ABaseEnemyAIController : public AAIController
{
	GENERATED_BODY()
public:
	ABaseEnemyAIController();
protected:
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
	UEnemyAIPerceptionComponent* AIPerceptionComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="AI")
	FName FocusOnKeyName = "Player";
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="AI")
	FName FightStatusKeyName = "FightStatus";
	virtual void OnPossess(APawn* InPawn) override;
	bool GetCanFocus() const;
	virtual void Tick(float DeltaSeconds) override;
private:
	AActor* GetFocusOnActor() const;
	
	void ChangeFightStatus(bool FightStatus);

	bool FightStatus = false;
};


