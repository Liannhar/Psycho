// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/FirstBoss/FirstBossEnemy.h"

#include "FirstBossAIController.h"
#include "FirstBossEffectActor.h"

void AFirstBossEnemy::StartEffectMoving(int32 NewStaminaCost)
{
	if(ChangeStaminaCost(NewStaminaCost)) return;
	UE_LOG(LogTemp,Display,TEXT("StartEffect"));
	if(GetWorld())
	{
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
		const auto ActorMesh = GetMesh();
		if(!ActorMesh) return;
		const auto EffectActor = GetWorld()->SpawnActor<AFirstBossEffectActor>(CurrentEffectActor,GetActorLocation(), GetActorRotation());
		if(EffectActor)
		{
			EffectActor->Create(GetMesh(),GetMesh()->SkeletalMesh);
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
	if(ChangeStaminaCost(CurrentAttackStaminaCost)) return;
	UE_LOG(LogTemp,Display,TEXT("Attack"));
	Super::Attack();
}

void AFirstBossEnemy::PreparationBossBeforeAttack(const EComboInput Type, const int32 NewCombo, const int32 NewCount, const bool NeedRandomCount,const int32 NewStaminaCost)
{
	CurrentAttackStaminaCost=NewStaminaCost;
	PreparationsBeforeTheAttack(Type,NewCombo,NewCount,NeedRandomCount);
}


bool AFirstBossEnemy::ChangeStaminaCost(const int32 NewCost)
{
	UE_LOG(LogTemp,Display,TEXT("CS: %d"),CurrentStamina);
	if(CurrentStamina==0)
	{
		AIController = Cast<AFirstBossAIController>(OwnController);
		AIController->SetBoolCurrentStamina(CurrentStamina);
		if(GetWorld() && !StaminaRecoverTimer.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(StaminaRecoverTimer,this,&AFirstBossEnemy::RecoverStamina,TimeStaminaRecover);
		}
		return true;
	}
	else
	{
		AIController = Cast<AFirstBossAIController>(OwnController);
		AIController->SetBoolCurrentStamina(CurrentStamina);
		CurrentStamina = FMath::Clamp(CurrentStamina - NewCost, 0, MaxStamina);
		return false;
	}
}

void AFirstBossEnemy::RecoverStamina()
{
	UE_LOG(LogTemp,Display,TEXT("Recover"));
	CurrentStamina=MaxStamina;
	AIController = Cast<AFirstBossAIController>(OwnController);
	if(GetWorld() && AIController)
	{
		AIController->SetBoolCurrentStamina(CurrentStamina);
		GetWorld()->GetTimerManager().ClearTimer(StaminaRecoverTimer);	
	}
	
}