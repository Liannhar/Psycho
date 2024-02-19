// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemy.h"

#include "AttackComponent.h"
#include "BaseEnemyAIController.h"
#include "Psycho/PsychoGameModeBase.h"
#include "HealthComponent.h"
#include "WeaponComponent.h"
#include "Weapons/BaseWeapon.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Engine/DecalActor.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/PlayerCharacter.h"

ABaseEnemy::ABaseEnemy()
{
	EnemyChannelCollision = CreateDefaultSubobject<UBoxComponent>("Enemy Channel Collision");
	EnemyChannelCollision->SetupAttachment(RootComponent);
	SmokeNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("SmokeNiagara");
	SmokeNiagaraComponent->SetupAttachment(RootComponent);
	EnemyChannelCollision->SetBoxExtent(FVector(1,1,1));
	EnemyChannelCollision->SetCollisionObjectType(ECC_GameTraceChannel1);
	
	DefaultMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
}

void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	OwnController = GetController();
}

void ABaseEnemy::Attack()
{
	auto const CurrentAiController = Cast<ABaseEnemyAIController>(OwnController);
	if(!CurrentAiController) return;

	const auto Distance = FVector::Dist(CurrentAiController->GetPlayerCharacter()->GetActorLocation(),GetActorLocation());
	if(Distance>130.0f) return;
	
	const auto AttackIndex = AttackComponent->GetAttackIndex();
	if(AttackIndex<=AttacksCount && !IsTakenDamage)
	{
		AttackComponent->CurrentComboAttack=ComboIndex;
		AttackComponent->StartComboAttack(AttackType);
		GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&ABaseEnemy::EndWait,1.0f);
		return;
	}
	GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&ABaseEnemy::EndEnemyAttack,3.0f);	
}

void ABaseEnemy::EndWait()
{
	if(!IsTakenDamage)
	{
		Attack();	
	}	
}

void ABaseEnemy::EndEnemyAttack()
{
	NotIsAttackingNow=true;
}

void ABaseEnemy::SetStartAttack()
{
	NotIsAttackingNow=false;
	GetWorldTimerManager().SetTimer(WaitNextAttemptAttack,this,&ABaseEnemy::EndEnemyAttack,5.0f);	
}

void ABaseEnemy::SetCanAttack(bool NewBool) const
{
	if(const auto AIController = Cast<ABaseEnemyAIController>(GetController()))
	{
		AIController->ChangeIsPawnCanAttack(NewBool);
	}
}

void ABaseEnemy::ChangeMaxSpeed(float NewSpeed) const
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


void ABaseEnemy::DamageDecalCreate(bool ActorRotationIsHead)
{
	const auto RandomZ = FMath::FRandRange(DamageDecalLocationZDownLimit,DamageDecalLocationZUPLimit);
	float RandomY;
	if(ActorRotationIsHead)
	{
		RandomY= FMath::FRandRange(DamageDecalLocationYLeftLimitHead,DamageDecalLocationYRightLimitHead);	
	}
	else
	{
		RandomY = FMath::FRandRange(DamageDecalLocationYLeftLimitBack,DamageDecalLocationYRightLimitBack);	
	}
	
	const auto RandomRoll = FMath::FRandRange(0.0f,360.0f);
	ADecalActor* decal = GetWorld()->SpawnActor<ADecalActor>(FVector(DamageDecalLocationXLimit,RandomY,RandomZ), FRotator(0.0f,0.0f,RandomRoll));
	if (decal)
	{
		decal->SetDecalMaterial(DamageDecalMaterialInterface);
		decal->SetLifeSpan(5.0f);
		decal->GetDecal()->DecalSize = FVector(7.0f, 4.0f, 14.0f);
		decal->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
		decal->SetActorRelativeLocation(FVector(DamageDecalLocationXLimit,RandomY,RandomZ)); 

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No decal spawned"));
	}
}

void ABaseEnemy::GetDamage(AActor* Actor)
{
	Super::GetDamage(Actor);

	const auto EnemyMesh=GetMesh();
	if(!EnemyMesh) return;
	
	/*if (UAnimInstance* AnimInstance = EnemyMesh->GetAnimInstance())
	{
		UE_LOG(LogTemp,Display,TEXT("1 %s"),*GetName());
		AnimInstance->StopAllMontages(0.0f);
	}*/

	
	
	if(HealthComponent->GetTakeDamageAnimMontage())
	{
		PlayAnimMontage(HealthComponent->GetTakeDamageAnimMontage());
	}
	
	if(const auto AIController = Cast<ABaseEnemyAIController>(GetController()))
	{
		AIController->ChangeIsPawnDamage(false);
	}

	if(!EndNiagaraEffectTimer.IsValid())
	{
		for (int32 i=0;i<MaterialsChangedForDamaged.Num();i++)
		{
			OldMaterials.Add(EnemyMesh->GetMaterial(i));
			EnemyMesh->SetMaterial(i,MaterialsChangedForDamaged[i]);
		}
	
		if( NewNiagaraSystem && SmokeNiagaraComponent->GetAsset())
		{
			OldNiagaraSystem=SmokeNiagaraComponent->GetAsset();
			SmokeNiagaraComponent->SetAsset(NewNiagaraSystem);
		}
	}
	GetWorld()->GetTimerManager().SetTimer(EndNiagaraEffectTimer,this,&ABaseEnemy::EndNiagaraEffect,TimeForEndNiagara);


	const auto DamageActorForwardVector = Actor->GetActorForwardVector();
	const auto ActorForwardVector = GetActorForwardVector();
	if(const auto DotProduct = FVector::DotProduct(DamageActorForwardVector, ActorForwardVector); DotProduct>0.0f)
	{
		DamageDecalCreate(false);
		SetActorLocation(GetActorLocation()+(ActorForwardVector+DamageActorForwardVector)*DistanceOfRepulsion);
	}
	else
	{
		DamageDecalCreate(true);
		SetActorLocation(GetActorLocation()+(-1*ActorForwardVector+DamageActorForwardVector)*DistanceOfRepulsion);
	}
	
	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(EndDamageEffectTimer,this,&ABaseEnemy::EndDamageEffects,TimeForWaitDamage);
}



void ABaseEnemy::EndNiagaraEffect()
{
	const auto EnemyMesh= GetMesh();
	if(!EnemyMesh) return;

	for (int32 i=0;i<OldMaterials.Num();i++)
	{
		EnemyMesh->SetMaterial(i,OldMaterials[i]);
	}
	OldMaterials.Empty();

	if(OldNiagaraSystem)
	{
		SmokeNiagaraComponent->SetAsset(OldNiagaraSystem);
	}
	GetWorld()->GetTimerManager().ClearTimer(EndNiagaraEffectTimer);
}

void ABaseEnemy::EndDamageEffects()
{
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
	Destroy();
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