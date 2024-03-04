// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/SmokedEnemies/SmokedEnemy.h"

#include "BaseWeapon.h"
#include "EnemySmokeActorEffectNiagara.h"
#include "NiagaraComponent.h"
#include "WeaponComponent.h"

ASmokedEnemy::ASmokedEnemy()
{
	FirstSmokeNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("FirstSmokeNiagara");
	FirstSmokeNiagaraComponent->SetupAttachment(RootComponent);
	SecondSmokeNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("SecondSmokeNiagara");
	SecondSmokeNiagaraComponent->SetupAttachment(RootComponent);
	ThirdSmokeNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("ThirdSmokeNiagara");
	ThirdSmokeNiagaraComponent->SetupAttachment(RootComponent);
}

void ASmokedEnemy::BeginPlay()
{
	Super::BeginPlay();
	ThirdSmokeNiagaraComponent->SetVisibility(false);
}

void ASmokedEnemy::GetDamage(AActor* Actor,const UDamageType* DamageType)
{
	Super::GetDamage(Actor,DamageType);
	const auto EnemyMesh=GetMesh();
	if(!EnemyMesh) return;
	if(!EndNiagaraEffectTimer.IsValid())
	{
		FirstSmokeNiagaraComponent->SetVisibility(false);
		SecondSmokeNiagaraComponent->SetVisibility(false);
		ThirdSmokeNiagaraComponent->SetVisibility(true);
	}
	GetWorld()->GetTimerManager().SetTimer(EndNiagaraEffectTimer,this,&ASmokedEnemy::EndNiagaraEffect,TimeForEndNiagara);
}

void ASmokedEnemy::Death()
{
	Super::Death();
	if(GetWorld())
	{
		GetWorld()->SpawnActor<AEnemySmokeActorEffectNiagara>(EnemySmokeDeathEffect,GetActorLocation(), GetActorRotation());
	}
	WeaponComponent->GetCurrentWeapon()->Destroy();
	Destroy();
}

void ASmokedEnemy::EndNiagaraEffect()
{
	const auto EnemyMesh= GetMesh();
	if(!EnemyMesh) return;
	
	FirstSmokeNiagaraComponent->SetVisibility(true);
	SecondSmokeNiagaraComponent->SetVisibility(true);
	ThirdSmokeNiagaraComponent->SetVisibility(false);
	GetWorld()->GetTimerManager().ClearTimer(EndNiagaraEffectTimer);
}
