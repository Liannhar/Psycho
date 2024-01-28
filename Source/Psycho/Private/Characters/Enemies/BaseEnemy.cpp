// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\Characters\Enemies\BaseEnemy.h"

#include "AttackComponent.h"
#include "BaseEnemyAIController.h"
#include "BaseWeapon.h"
#include "EnemyAIPerceptionComponent.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Psycho/PsychoGameModeBase.h"

ABaseEnemy::ABaseEnemy()
{
	
}


void ABaseEnemy::Attack()
{
	if(const auto AttackkComponent = GetAttackComponent())
	{
		const auto AttackIndex = AttackkComponent->GetAttackIndex();
		if(AttackIndex<=AttacksCount && !IsTakenDamage)
		{
			AttackkComponent->StartAttack(LightAttack);
			GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&ABaseEnemy::EndWait,1.0f);	
			return;
		}
		GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&ABaseEnemy::EndEnemyAttack,3.0f);	
	}
}

void ABaseEnemy::EndWait()
{
	Attack();
}

void ABaseEnemy::EndEnemyAttack()
{
	NotIsAttackingNow=true;
}

void ABaseEnemy::ChangeCountCombo()
{
	AttacksCount = FMath::RandRange(0, 2);
}

void ABaseEnemy::BlockAttack()
{
	//Heres Block
}



void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	const auto HealthhComponent = GetHealthComponent();
	HealthhComponent->OnTakeDamage.AddUObject(this,&ABaseEnemy::TakingDamage);
}

void ABaseEnemy::SetStartAttack()
{
	NotIsAttackingNow=false;
	GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&ABaseEnemy::EndEnemyAttack,5.0f);	
}

void ABaseEnemy::TakingDamage()
{
	IsTakenDamage=true;
	GetWorldTimerManager().SetTimer(TimerDamage,this,&ABaseEnemy::DontTakeDamage,TimeForWaitDamage);
}

void ABaseEnemy::DontTakeDamage()
{
	IsTakenDamage=false;
}




void ABaseEnemy::ChangeMaxSpeed(float NewSpeed) const
{
	const auto CharacterMovementComponent =Cast<UCharacterMovementComponent>(GetMovementComponent());
	if(!CharacterMovementComponent) return;

	CharacterMovementComponent->MaxWalkSpeed=NewSpeed;
}

void ABaseEnemy::Death()
{
	Super::Death();

	const auto AIController = Cast<ABaseEnemyAIController>(GetController());
	if(!AIController) return;

	const auto Component = AIController->GetComponentByClass(UEnemyAIPerceptionComponent::StaticClass());
	const auto PerceptionComponent = Cast<UEnemyAIPerceptionComponent>(Component);
	if(!PerceptionComponent) return;
	
	const auto World = GetWorld();
	if(!World) return;
	const auto GameMode =  World->GetAuthGameMode();
	const auto PsychoGameMode = Cast<APsychoGameModeBase>(GameMode);
	PsychoGameMode->ChangeEnemiesCount(this);
	WeaponComponent->GetCurrentWeapon()->Destroy();
	Destroy();
}

bool ABaseEnemy::GetLastAttackIsHeavy() const
{
	if(const auto HealthhComponent = GetHealthComponent())
	{
		return HealthhComponent->GetLastAttackIsHeavy();
	}
	return false;
}
