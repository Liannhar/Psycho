// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/FirstBoss/FirstBossEnemy.h"

#include "BaseWeapon.h"
#include "FirstBossAIController.h"
#include "FirstBossEffectActor.h"
#include "KeyActor.h"
#include "WeaponComponent.h"
#include "Animation/AnimNode_StateMachine.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void AFirstBossEnemy::StartEffectMoving(const int32 NewStaminaCost)
{
	if(ChangeStaminaCost(NewStaminaCost)) return;
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
		if(const auto EffectActor = GetWorld()->SpawnActor<AFirstBossEffectActor>(CurrentEffectActor,GetActorLocation(), GetActorRotation()))
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
	Super::Attack();
}

void AFirstBossEnemy::PreparationBossBeforeAttack(const EComboInput Type, const int32 NewCombo, const int32 NewCount, const bool NeedRandomCount,const int32 NewStaminaCost)
{
	CurrentAttackStaminaCost=NewStaminaCost;
	PreparationsBeforeTheAttack(Type,NewCombo,NewCount,NeedRandomCount);
}

void AFirstBossEnemy::DeathConfigurations()
{
	WeaponComponent->GetCurrentWeapon()->Destroy();
	if(GetWorld())
	{
		const auto NewSpawnedKey = GetWorld()->SpawnActor<AKeyActor>(CardKey,GetActorLocation(), GetActorRotation());
		if(NewSpawnedKey)
		{
			NewSpawnedKey->SetDoorThatNeedKey(DoorThatNeedBossKey);
			NewSpawnedKey->EnablePhysics();
		}
		const auto NewSpawnedWeapon = GetWorld()->SpawnActor<ABaseWeapon>(NewWeaponClassForPlayer,WeaponComponent->GetCurrentWeapon()->GetActorLocation(), WeaponComponent->GetCurrentWeapon()->GetActorRotation());
		if (NewSpawnedWeapon)
		{
			NewSpawnedWeapon->EnablePhysics();
		}
	}
}


bool AFirstBossEnemy::ChangeStaminaCost(const int32 NewCost)
{
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
	
	AIController = Cast<AFirstBossAIController>(OwnController);
	AIController->SetBoolCurrentStamina(CurrentStamina);
	CurrentStamina = FMath::Clamp(CurrentStamina - NewCost, 0, MaxStamina);
	return false;
}

void AFirstBossEnemy::UpdateStaminaAI()
{
	AIController = Cast<AFirstBossAIController>(OwnController);
	if(GetWorld() && AIController)
	{
		/*const auto AnimInstance = GetMesh()->GetAnimInstance();
		const auto StateName = AnimInstance->GetStateMachineInstance(0);
		const auto Time = AnimInstance->GetRelevantAnimTimeRemaining(0,2);
		UE_LOG(LogTemp,Display,TEXT("%s"),*StateName.ToString());*/
		AIController->SetBoolCurrentStamina(CurrentStamina);
		GetWorld()->GetTimerManager().ClearTimer(StaminaRecoverTimer);	
	}
}

void AFirstBossEnemy::RecoverStamina()
{
	UE_LOG(LogTemp,Display,TEXT("Recover"));
	CurrentStamina=MaxStamina;
	GetWorld()->GetTimerManager().SetTimer(StaminaRecoverTimer,this,&AFirstBossEnemy::UpdateStaminaAI,1.5f);
}



void AFirstBossEnemy::Death()
{
	Super::Death();
	float DeathTime = PlayAnimMontage(DeathAnimMontage);
	SetActorEnableCollision(false);
	GetWorld()->GetTimerManager().SetTimer(DeathTimer,this,&AFirstBossEnemy::AfterDeath,DeathTime-0.3f);
}

void AFirstBossEnemy::AfterDeath() const
{
	GetMesh()->GetAnimInstance()->Montage_Pause(DeathAnimMontage);
	EnemyChannelCollision->Deactivate();
}