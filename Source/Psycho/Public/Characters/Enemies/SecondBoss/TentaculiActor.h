// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SecondBossCoreTypes.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "TentaculiActor.generated.h"

class ATentaculiDamage;
class APlayerCharacter;
class UNiagaraComponent;

UCLASS()
class PSYCHO_API ATentaculiActor : public APawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATentaculiActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Tentaculi")
	float Damage=10.0f;

	UPROPERTY(EditAnywhere,Category="Tentaculi")
	float WaitTimeAfterAttack=10.0f;
	UPROPERTY(EditAnywhere,Category="Tentaculi")
	float WaitTimeAfterCheckRadius=0.3f;
	UPROPERTY(EditAnywhere,Category="Tentaculi")
	float StartWaitTime=2.0f;
	UPROPERTY(EditAnywhere,Category="Tentaculi")
	double HeightAttackZ=20.f;
	FTimerHandle TimerHandle;


	void EndWait();
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tentaculi")
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	APlayerCharacter* Player;

	bool CheckIsPlayerNearTentaculi(const FVector& Distance);
	void NiagaraChangePosition();

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Tentaculi")
	FTentaculiParameters TentaculiParameters;
	

	FVector CurrentLocation;

	FTimerHandle AttackTimer;
	void NiagaraChangeBackPosition();
    void ReturnInStartPosition(float WaitNextAttackAttemptTime);
	UFUNCTION(BlueprintCallable)
	void OnComponentBeginOverlap();

public:
	void SetPlayer(APlayerCharacter*& NewPlayer){Player=NewPlayer;}

	void Activate() const;
	void Deactivate() const;
	
};
