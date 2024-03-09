// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseEnemyAIController.generated.h"

class APlayerCharacter;
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
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="AI")
	FName IsPawnNotDamagedKeyName = "IsNotDamaged";
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="AI")
	FName IsPawnCanAttackKeyName = "IsCanAttack";
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="AI")
	FName IsPawnStun="IsStun";
	virtual void OnPossess(APawn* InPawn) override;
	virtual bool GetCanFocus() const;
	virtual void Tick(float DeltaSeconds) override;
	
	AActor* GetFocusOnActor() const;
	
	void ChangeFightStatus(const bool FightStatus);

	bool FightStatus = false;

	UPROPERTY()
	APlayerCharacter* PlayerCharacter;
	
public:
	
	AActor* GetPlayerActor() const ;
	void ChangeIsPawnDamage(const bool& NewBool);
	void ChangeIsPawnCanAttack(const bool& NewBool);
	void ChangeIsStun(const bool& NewBool);

	APlayerCharacter* GetPlayerCharacter() const{return PlayerCharacter;}
};


