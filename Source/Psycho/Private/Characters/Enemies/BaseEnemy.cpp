// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\Characters\Enemies\BaseEnemy.h"

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
	//heres Attack
}

void ABaseEnemy::BlockAttack()
{
	//Heres Block
}

void ABaseEnemy::GetDamage()
{
	//heres enemy take damages
}


void ABaseEnemy::ChangeMaxSpeed(float NewSpeed)
{
	const auto CharacterMovementComponent =Cast<UCharacterMovementComponent>(GetMovementComponent());
	if(!CharacterMovementComponent) return;

	CharacterMovementComponent->MaxWalkSpeed=NewSpeed;
}