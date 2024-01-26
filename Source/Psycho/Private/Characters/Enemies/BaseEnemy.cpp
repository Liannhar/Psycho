// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\..\Public\Characters\Enemies\BaseEnemy.h"

#include "AttackComponent.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "Weapons/BaseWeapon.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ABaseEnemy::ABaseEnemy()
{
	EnemyChannelCollision = CreateDefaultSubobject<UBoxComponent>("Enemy Channel Collision");
	EnemyChannelCollision->SetupAttachment(RootComponent);
	EnemyChannelCollision->SetBoxExtent(FVector(1,1,1));
	EnemyChannelCollision->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
}

void ABaseEnemy::Attack()
{
	UE_LOG(LogTemp,Display,TEXT("A%d"),NotIsAttackingNow?1:0);
	if(const auto AttackkComponent = GetAttackComponent())
	{
		const auto AttackIndex = AttackkComponent->GetAttackIndex();
		if(AttackIndex<=AttacksCount && !IsTakenDamage)
		{
			NotIsAttackingNow=false;		
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
	OwnController = GetController();
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


void ABaseEnemy::Deactivate()
{
	SetActorHiddenInGame(true);
	GetWeaponComponent()->GetCurrentWeapon()->SetActorHiddenInGame(true);
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	// Hide all attached actors
	// TArray<AActor*> AttachedActors;
	// GetAttachedActors(AttachedActors);
	// for (AActor* Actor : AttachedActors)
	// {
	// 	Actor->SetActorHiddenInGame(true);
	// }
	GetMovementComponent()->StopActiveMovement();
	OwnController->UnPossess();
}

void ABaseEnemy::Reactivate()
{
	SetActorHiddenInGame(false);
	GetWeaponComponent()->GetCurrentWeapon()->SetActorHiddenInGame(false);
	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	// Unhide all attached actors
	// TArray<AActor*> AttachedActors;
	// GetAttachedActors(AttachedActors);
	// for (AActor* Actor : AttachedActors)
	// {
	// 	Actor->SetActorHiddenInGame(false);
	// }
	OwnController->Possess(this);
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
