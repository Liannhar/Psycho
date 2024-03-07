// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/SmokedEnemies/EnemySmokeActorEffectNiagara.h"

#include "NiagaraComponent.h"

AEnemySmokeActorEffectNiagara::AEnemySmokeActorEffectNiagara()
{
	PrimaryActorTick.bCanEverTick = false;
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("FirstSmokeNiagara");
	RootComponent = NiagaraComponent;
}

void AEnemySmokeActorEffectNiagara::BeginPlay()
{
	Super::BeginPlay();
	NiagaraComponent->OnSystemFinished.AddDynamic(this,&AEnemySmokeActorEffectNiagara::EndNiagaraEffect);
	NiagaraComponent->Activate();
}

void AEnemySmokeActorEffectNiagara::EndNiagaraEffect(UNiagaraComponent* PSystem)
{
	Destroy();
}

