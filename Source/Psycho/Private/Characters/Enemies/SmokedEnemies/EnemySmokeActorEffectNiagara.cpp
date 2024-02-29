// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/SmokedEnemies/EnemySmokeActorEffectNiagara.h"

#include "NiagaraComponent.h"

// Sets default values
AEnemySmokeActorEffectNiagara::AEnemySmokeActorEffectNiagara()
{
	PrimaryActorTick.bCanEverTick = false;
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("FirstSmokeNiagara");
	NiagaraComponent->SetupAttachment(RootComponent);
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

