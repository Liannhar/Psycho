// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\Characters\Enemies\BaseEnemy.h"

#include "AttackComponent.h"
#include "HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemy::ABaseEnemy()
{
	
}

bool ABaseEnemy::IsEnemyAttacking()
{
	return IsAttacking;
}

void ABaseEnemy::Attack()
{
	if(const auto AttackkComponent = GetAttackComponent())
	{
		const auto AttackIndex = AttackkComponent->GetAttackIndex();
		if(AttackIndex<=AttacksCount && !IsTakenDamage)
		{
			NotIsAttackingNow=false;		
			AttackkComponent->StartAttack(LightAttack);
			GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&ABaseEnemy::EndWait,0.5f);	
		}
	}
}

void ABaseEnemy::EndWait()
{
	NotIsAttackingNow=true;
	Attack();
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

UAttackComponent* ABaseEnemy::GetAttackComponent() const
{
	const auto Component = GetComponentByClass(UAttackComponent::StaticClass());
	if(!Component) return nullptr;

	if(const auto AttackkComponent = Cast<UAttackComponent>(Component)) return AttackkComponent;
	return nullptr;
}

UHealthComponent* ABaseEnemy::GetHealthComponent() const
{
	const auto Component = GetComponentByClass(UHealthComponent::StaticClass());
	if(!Component) return nullptr;

	if(const auto HealthhComponent = Cast<UHealthComponent>(Component)) return HealthhComponent;
	return nullptr;
}

bool ABaseEnemy::GetLastAttackIsHeavy() const
{
	if(const auto HealthhComponent = GetHealthComponent())
	{
		return HealthhComponent->GetLastAttackIsHeavy();
	}
	return false;
}
