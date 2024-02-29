// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/BaseEnemy.h"
#include "SmokedEnemy.generated.h"

class AEnemySmokeActorEffectNiagara;
/**
 * 
 */
UCLASS()
class PSYCHO_API ASmokedEnemy : public ABaseEnemy
{
	GENERATED_BODY()
public:
	ASmokedEnemy();
protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="Niagara")
	UNiagaraComponent* FirstSmokeNiagaraComponent;
	UPROPERTY(EditAnywhere,Category="Niagara")
	UNiagaraComponent* SecondSmokeNiagaraComponent;
	UPROPERTY(EditAnywhere,Category="Niagara")
	UNiagaraComponent* ThirdSmokeNiagaraComponent;
	UPROPERTY(EditAnywhere,Category="Effect")
	TSubclassOf<AEnemySmokeActorEffectNiagara> EnemySmokeDeathEffect;

	virtual void GetDamage(AActor* Actor,const UDamageType* DamageType) override;

	virtual void Death() override;
	void EndNiagaraEffect();
	UPROPERTY(EditAnywhere,Category="Damage")
	float TimeForEndNiagara=2.0f;
	FTimerHandle EndNiagaraEffectTimer;
};
