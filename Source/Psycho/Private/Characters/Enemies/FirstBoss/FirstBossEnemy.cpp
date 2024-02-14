// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/FirstBoss/FirstBossEnemy.h"

#include "FirstBossEffectActor.h"

void AFirstBossEnemy::StartEffectMoving(int32 NewStaminaCost)
{
	if(CurrentStamina==0) return;
	if(GetWorld())
	{
		ChangeStaminaCost(NewStaminaCost);
		GetWorld()->GetTimerManager().SetTimer(EffectTImer,this,&AFirstBossEnemy::MakeEffect,EffectTime,true);
	}
}

void AFirstBossEnemy::EndEffectMoving()
{
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(EffectTImer);
	}
}

void AFirstBossEnemy::MakeEffect()
{
	if(GetWorld())
	{
		const FActorSpawnParameters SpawnInfo;
		const auto ActorMesh = GetMesh();
		if(!ActorMesh) return;
		if(const auto EffectActor = GetWorld()->SpawnActor<AFirstBossEffectActor>(ActorMesh->GetRelativeLocation(), ActorMesh->GetRelativeRotation(), SpawnInfo))
		{
			EffectActor->Create(GetMesh(),Cast<USkeletalMesh>(GetMesh()));
		}
	}
}

void AFirstBossEnemy::BeginPlay()
{
	Super::BeginPlay();
	CurrentStamina=MaxStamina;
	
}

void AFirstBossEnemy::Attack()
{
	if(CurrentStamina==0) return;
	Super::Attack();
}

void AFirstBossEnemy::PreparationBossBeforeAttack(const EComboInput Type, const int32 NewCombo, const int32 NewCount, const bool NeedRandomCount,const int32 NewStaminaCost)
{
	if(CurrentStamina==0) return;
	ChangeStaminaCost(NewStaminaCost);
	PreparationsBeforeTheAttack(Type,NewCombo,NewCount,NeedRandomCount);
}


void AFirstBossEnemy::ChangeStaminaCost(int32 NewCost)
{
	CurrentStamina = FMath::Clamp(CurrentStamina - NewCost, 0, MaxStamina);
	if(CurrentStamina==0)
	{
		if(GetWorld() && !StaminaRecoverTimer.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(StaminaRecoverTimer,this,&AFirstBossEnemy::RecoverStamina,TimeStaminaRecover);
		}
	}
}

void AFirstBossEnemy::RecoverStamina()
{
	CurrentStamina=MaxStamina;
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(StaminaRecoverTimer);	
	}
	
}


