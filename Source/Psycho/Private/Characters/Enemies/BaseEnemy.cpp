// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "AttackComponent.h"
#include "BaseEnemyAIController.h"
#include "FirstBossEnemy.h"
#include "Psycho/PsychoGameModeBase.h"
#include "HealthComponent.h"
#include "MotionWarpingComponent.h"
#include "WeaponComponent.h"
#include "Weapons/BaseWeapon.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/DecalActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"

ABaseEnemy::ABaseEnemy()
{
	EnemyChannelCollision = CreateDefaultSubobject<UBoxComponent>("Enemy Channel Collision");
	EnemyChannelCollision->SetupAttachment(RootComponent);
	
	EnemyChannelCollision->SetBoxExtent(FVector(1,1,1));
	EnemyChannelCollision->SetCollisionObjectType(ECC_GameTraceChannel1);
	
	DefaultMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	OwnController = GetController();

	if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
	{
		Player->GetHealthComponent()->OnDeath.AddUObject(this, &ABaseEnemy::OnPlayerDied);
	}
}

void ABaseEnemy::Attack()
{
	auto const CurrentAiController = Cast<ABaseEnemyAIController>(OwnController);
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
		AttackComponent->CurrentComboAttack=ComboIndex;
		AttackComponent->StartComboAttack(AttackType);
		GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&AFirstBossEnemy::EndWait,0.3f);
		return;
	}
	GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&AFirstBossEnemy::EndEnemyAttack,EndEnemyAttackTime);	
}

void ABaseEnemy::EndWait()
{
	if(!IsTakenDamage || Cast<AFirstBossEnemy>(this))
	{
		GetWorldTimerManager().ClearTimer(WaitNextAttemptAttack);
		Attack();
		return;
	}
	EndEnemyAttack();
}

void ABaseEnemy::EndEnemyAttack()
{
	NotIsAttackingNow=true;
	GetWorldTimerManager().ClearTimer(WaitNextAttemptAttack);
}


void ABaseEnemy::SetStartAttack()
{
	NotIsAttackingNow=false;
	GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&ABaseEnemy::EndEnemyAttack,5.0f);	
}

void ABaseEnemy::SetCanAttack(const bool& NewBool) const
{
	if(const auto AIController = Cast<ABaseEnemyAIController>(GetController()))
	{
		AIController->ChangeIsPawnCanAttack(NewBool);
	}
}

void ABaseEnemy::ChangeMaxSpeed(const float& NewSpeed) const
{
	const auto CharacterMovementComponent =Cast<UCharacterMovementComponent>(GetMovementComponent());
	if(!CharacterMovementComponent) return;
	CharacterMovementComponent->MaxWalkSpeed=NewSpeed;
}

void ABaseEnemy::PreparationsBeforeTheAttack(const EComboInput Type, const int32 NewCombo, const int32 NewCount, const bool NeedRandomCount)
{
	ComboIndex=NewCombo;
	AttackType = Type;
	if(NeedRandomCount) AttacksCount = FMath::RandRange(0, NewCount);	
	else AttacksCount = NewCount;
}

void ABaseEnemy::BlockAttack()
{
	//Heres Block
}


void ABaseEnemy::DamageDecalCreate(const bool& ActorRotationIsHead) const
{
	const auto RandomZ = FMath::FRandRange(DamageDecalLocationZDownLimit,DamageDecalLocationZUPLimit);
	float RandomY;
	if(ActorRotationIsHead)
	{
		RandomY= FMath::FRandRange(DamageDecalLocationYLeftLimitHead,DamageDecalLocationYRightLimitHead);	
	}
	else
	{
		RandomY=FMath::FRandRange(DamageDecalLocationYLeftLimitBack,DamageDecalLocationYRightLimitBack);	
	}
	
	const auto RandomRoll = FMath::FRandRange(0.0f,360.0f);
	if (ADecalActor* Decal = GetWorld()->SpawnActor<ADecalActor>(FVector(DamageDecalLocationXLimit,RandomY,RandomZ), FRotator(0.0f,0.0f,RandomRoll)))
	{
		Decal->SetDecalMaterial(DamageDecalMaterialInterface);
		Decal->SetLifeSpan(5.0f);
		Decal->GetDecal()->DecalSize = DecalSizeVector;
		Decal->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		Decal->SetActorRelativeLocation(FVector(DamageDecalLocationXLimit,RandomY,RandomZ)); 
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No decal spawned"));
	}
}

void ABaseEnemy::GetDamage(AActor* Actor,const UDamageType* DamageType)
{
	Super::GetDamage(Actor,DamageType);

	IsTakenDamage=true;
	
	if(const auto AIController = Cast<ABaseEnemyAIController>(GetController()))
	{
		AIController->ChangeIsPawnDamage(false);
	}
	AttackDirection = 0;
	DistanceOfRepulsion = 0.0f;
	if(const auto Player = Cast<APlayerCharacter>(Actor))
	{
		AttackDirection = Player->GetAttackComponent()->GetCurrentAttackDirection();
		DistanceOfRepulsion = Player->GetAttackComponent()->GetCurrentAttackRepulsion();
	}
	
	const auto DamageActorForwardVector = Actor->GetActorForwardVector();
	const auto ActorForwardVector = GetActorForwardVector();
	FTransform HitReactTransform = FTransform();
	if(const auto DotProduct = FVector::DotProduct(DamageActorForwardVector, ActorForwardVector); DotProduct>0.0f)
	{	
		DamageDecalCreate(false);
	}
	else
	{
		DamageDecalCreate(true);
		if(AttackDirection!=0)
		{	
			const auto NewLocation = FVector(GetActorLocation().X+GetActorRightVector().X*AttackDirection*DistanceOfRepulsion*10.0f,GetActorLocation().Y+GetActorRightVector().Y*AttackDirection*DistanceOfRepulsion*10.0f,GetActorLocation().Z);
			HitReactTransform.SetLocation(NewLocation);
			HitReactTransform.SetRotation(GetActorRotation().Quaternion());
		}
		else
		{
			const auto NewLocation = GetActorLocation()+(ActorForwardVector+DamageActorForwardVector)*DistanceOfRepulsion;
			HitReactTransform.SetLocation(NewLocation);
			HitReactTransform.SetRotation(GetActorRotation().Quaternion());
		}
	}
	MotionWarpingComponent->AddOrUpdateWarpTargetFromTransform("React",HitReactTransform);
	PlayAnimMontage(HealthComponent->GetTakeDamageAnimMontage(AttackDirection));	
	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(EndDamageEffectTimer,this,&ABaseEnemy::EndDamageEffects,TimeForWaitDamage);
}

void ABaseEnemy::EndDamageEffects()
{
	IsTakenDamage=false;
	if(const auto AIController = Cast<ABaseEnemyAIController>(GetController()))
	{
		AIController->ChangeIsPawnDamage(true);
	}
	
	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().ClearTimer(EndDamageEffectTimer);
}

bool ABaseEnemy::GetLastAttackIsHeavy() const
{
	return HealthComponent->GetLastAttackIsHeavy();
}

void ABaseEnemy::Death()
{
	Super::Death();
	
	const auto World = GetWorld();
	if(!World) return;
	const auto GameMode =  World->GetAuthGameMode();
	const auto PsychoGameMode = Cast<APsychoGameModeBase>(GameMode);
	PsychoGameMode->ChangeEnemiesCount(this);
	WeaponComponent->GetCurrentWeapon()->Destroy();
}


void ABaseEnemy::OnPlayerDied()
{
	PlayerDied.Execute();
}


void ABaseEnemy::Deactivate(float SpeedReduceMultiplier)
{
	ChangeMaxSpeed(GetCharacterMovement()->MaxWalkSpeed * SpeedReduceMultiplier);
	GetAttackComponent()->MultiplyAttackSpeed(SpeedReduceMultiplier);
	// SetActorHiddenInGame(true);
	// GetWeaponComponent()->GetCurrentWeapon()->SetActorHiddenInGame(true);
	// GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel1);
	// GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
	// // Hide all attached actors
	// // TArray<AActor*> AttachedActors;
	// // GetAttachedActors(AttachedActors);
	// // for (AActor* Actor : AttachedActors)
	// // {
	// // 	Actor->SetActorHiddenInGame(true);
	// // }
	// GetMovementComponent()->StopActiveMovement();
	// OwnController->UnPossess();
}

void ABaseEnemy::Reactivate()
{
	ChangeMaxSpeed(DefaultMaxWalkSpeed);
	GetAttackComponent()->ResetAttackSpeedToDefault();
	// SetActorHiddenInGame(false);
	// GetWeaponComponent()->GetCurrentWeapon()->SetActorHiddenInGame(false);
	// GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_Pawn);
	// GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Block);
	// // Unhide all attached actors
	// // TArray<AActor*> AttachedActors;
	// // GetAttachedActors(AttachedActors);
	// // for (AActor* Actor : AttachedActors)
	// // {
	// // 	Actor->SetActorHiddenInGame(false);
	// // }
	// OwnController->Possess(this);
}