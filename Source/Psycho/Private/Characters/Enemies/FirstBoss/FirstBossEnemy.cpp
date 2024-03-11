// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/FirstBoss/FirstBossEnemy.h"

#include "BaseWeapon.h"
#include "FirstBossAIController.h"
#include "FirstBossEffectActor.h"
#include "KeyActor.h"
#include "WeaponComponent.h"
#include "Components/BoxComponent.h"
#include "Player/PlayerCharacter.h"

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

void AFirstBossEnemy::Attack()
{
	auto const CurrentAiController = Cast<AFirstBossAIController>(OwnController);
	if(!CurrentAiController)
	{
		GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&ABaseEnemy::EndEnemyAttack,EndEnemyAttackTime);	
		return;
	}
	if(CurrentAiController->GetPlayerCharacter())
	{

		const auto Distance = FVector::Dist(CurrentAiController->GetPlayerCharacter()->GetActorLocation(),GetActorLocation());
		if(Distance>100.0f)
		{
			GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&ABaseEnemy::EndEnemyAttack,EndEnemyAttackTime);	
			return;
		}	
	}
	const auto AttackIndex = AttackComponent->GetAttackIndex();
	if(AttackIndex<=AttacksCount && (!IsTakenDamage || Cast<AFirstBossEnemy>(this)))
	{
		if(ChangeStaminaCost(CurrentAttackStaminaCost))
		{
			GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&AFirstBossEnemy::EndEnemyAttack,EndEnemyAttackTime);	
			return;
		}
		AttackComponent->CurrentComboAttack=ComboIndex;
		AttackComponent->StartComboAttack(AttackType);
		GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&AFirstBossEnemy::EndWait,0.3f);
		return;
	}
	GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&AFirstBossEnemy::EndEnemyAttack,EndEnemyAttackTime);	

}


bool AFirstBossEnemy::ChangeStaminaCost(const int32& NewCost)
{
	AIController = Cast<AFirstBossAIController>(OwnController);
	AIController->SetBoolCurrentStamina(CurrentStamina);
	UE_LOG(LogTemp,Display,TEXT("CS %d"),CurrentStamina);
	if(CurrentStamina==0)
	{
		StaminaHaveRemainder=false;
		GetMesh()->GetAnimInstance()->StopAllMontages(0.0f);
		
		if(GetWorld() && !StaminaRecoverTimer.IsValid())
		{
			GetWorld()->GetTimerManager().SetTimer(StaminaRecoverTimer,this,&AFirstBossEnemy::RecoverStamina,TimeStaminaRecover);
		}
		return true;
	}
	
	CurrentStamina = FMath::Clamp(CurrentStamina - NewCost, 0, MaxStamina);
	if(CurrentStamina==0)
	{
		StaminaHaveRemainder=true;
	}
	return false;
}

void AFirstBossEnemy::UpdateStaminaAI()
{
	AIController = Cast<AFirstBossAIController>(OwnController);
	if(GetWorld() && AIController)
	{
		AIController->SetBoolCurrentStamina(CurrentStamina);
		GetWorld()->GetTimerManager().ClearTimer(StaminaRecoverTimer);	
	}
}

void AFirstBossEnemy::RecoverStamina()
{
	UE_LOG(LogTemp,Display,TEXT("Recover"));
	CurrentStamina=MaxStamina;
	StaminaHaveRemainder=false;
	
	GetWorld()->GetTimerManager().SetTimer(StaminaRecoverTimer,this,&AFirstBossEnemy::UpdateStaminaAI,1.5f);
}



void AFirstBossEnemy::Death(ABaseCharacter* Character)
{
	Super::Death(Character);
	const float DeathTime = PlayAnimMontage(DeathAnimMontage);
	SetActorEnableCollision(false);
	GetWorld()->GetTimerManager().SetTimer(DeathTimer,this,&AFirstBossEnemy::AfterDeath,DeathTime-0.3f);
}

void AFirstBossEnemy::AfterDeath() const
{
	GetMesh()->GetAnimInstance()->Montage_Pause(DeathAnimMontage);
	EnemyChannelCollision->Deactivate();
}
