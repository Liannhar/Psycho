// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySmokeActorEffectNiagara.generated.h"

class UNiagaraComponent;

UCLASS()
class PSYCHO_API AEnemySmokeActorEffectNiagara : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemySmokeActorEffectNiagara();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,Category="Niagara")
	UNiagaraComponent* NiagaraComponent;
	UFUNCTION()
	void EndNiagaraEffect(UNiagaraComponent* PSystem);

};
