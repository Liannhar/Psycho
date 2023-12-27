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

UAttackComponent* ABaseEnemy::GetAttackComponent()
{
	const auto Component = GetComponentByClass(UAttackComponent::StaticClass());
	if(!Component) return nullptr;

	const auto AttacckComponent = Cast<UAttackComponent>(Component);
	if(AttacckComponent) return AttacckComponent;
	return nullptr;
}

void ABaseEnemy::Attack()
{
	if(const auto AttackComponentt = GetAttackComponent())
	{
		
		const auto AttackIndex = AttackComponentt->GetAttackIndex();
		UE_LOG(LogTemp,Display,TEXT("ac%d"),AttacksCount);
		UE_LOG(LogTemp,Display,TEXT("ai%d"),AttackIndex);
		if(AttackIndex<=AttacksCount && !IsTakenDamage)
		{
			AttackComponentt->StartAttack(LightAttack);
			GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&ABaseEnemy::EndWait,0.5f);	
		}
	}
}

void ABaseEnemy::ChangeCountCombo()
{
	AttacksCount = FMath::RandRange(0, 2);
}

void ABaseEnemy::BlockAttack()
{
	//Heres Block
}

void ABaseEnemy::GetDamage()
{
	//heres enemy take damages
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	const auto Component = GetComponentByClass(UHealthComponent::StaticClass());
	const auto NHealthComponent = Cast<UHealthComponent>(Component);
	NHealthComponent->OnTakeDamage.AddUObject(this,&ABaseEnemy::TakingDamage);
	
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

void ABaseEnemy::EndWait()
{
	Attack();
}


void ABaseEnemy::ChangeMaxSpeed(float NewSpeed) const
{
	const auto CharacterMovementComponent =Cast<UCharacterMovementComponent>(GetMovementComponent());
	if(!CharacterMovementComponent) return;

	CharacterMovementComponent->MaxWalkSpeed=NewSpeed;
}
