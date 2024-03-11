// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/SecondBoss/SecondBossEnemy.h"

#include "FirstStageSecondBossComponent.h"
#include "HealthComponent.h"
#include "NiagaraComponent.h"
#include "SecondBossEnemyAIController.h"
#include "SecondStageSecondBossComponent.h"
#include "ThirdStageSecondBossComponent.h"
#include "Player/PlayerCharacter.h"

ASecondBossEnemy::ASecondBossEnemy()
{
	FirstStageSecondBossComponent=CreateDefaultSubobject<UFirstStageSecondBossComponent>("FirstStage");
	SecondStageSecondBossComponent=CreateDefaultSubobject<USecondStageSecondBossComponent>("SecondStage");
	ThirdStageSecondBossComponent=CreateDefaultSubobject<UThirdStageSecondBossComponent>("ThirdStage");
	SmokeNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("FirstSmokeNiagara");
	SmokeNiagaraComponent->SetupAttachment(RootComponent);
}

void ASecondBossEnemy::BeginPlay()
{
	Super::BeginPlay();
	SecondBossEnemyAIController=Cast<ASecondBossEnemyAIController>(OwnController);
}

void ASecondBossEnemy::ChangeStage(const ESecondBossStages& NewStage)
{
	switch (NewStage)
	{
	case First:
		{
			BehaviorTreeAsset=FirstStageSecondBossComponent->GetBehaviorTree();
			SecondBossEnemyAIController->ChangeBTStage();
			FirstStageSecondBossComponent->FirstStageAction();
			NextStage=Second;
			break;
		}
	case Second:
		{
			BehaviorTreeAsset=SecondStageSecondBossComponent->GetBehaviorTree();
			SecondBossEnemyAIController->ChangeBTStage();
			SecondStageSecondBossComponent->SecondStageStartAction();
			NextStage=Third;
			break;
		}
	case Third:
		{
			BehaviorTreeAsset=ThirdStageSecondBossComponent->GetBehaviorTree();
			SecondBossEnemyAIController->ChangeBTStage();
			ThirdStageSecondBossComponent->ThirdStageStartAction();
			NextStage=First;
			break;
		}
	}
}





void ASecondBossEnemy::ChangeInvulnerable(const bool&& NewBool)
{
	HealthComponent->bIsInvulnerable=NewBool;
}

void ASecondBossEnemy::EndStage()
{
	ChangeStage(NextStage);
}

void ASecondBossEnemy::StartBoss()
{
	NextStage=First;
	ChangeStage(NextStage);
}

void ASecondBossEnemy::ScreamAttack()
{
	bScreamAttack=true;
	const float ScreamTime = PlayAnimMontage(ScreamMontage);
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(ScreamTimer,this,&ASecondBossEnemy::EndScreamAttack,ScreamTime);
	}
	ScreamLogic();
}

void ASecondBossEnemy::ScreamLogic()
{
	FVector Start = GetActorLocation();
	FVector End = SecondBossEnemyAIController->GetPlayerCharacter()->GetActorLocation();
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	if (!UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, ScreamRadius, ObjectTypesArray, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true)) return;
	
	if(const auto&& Player = Cast<APlayerCharacter>(HitResult.GetActor()))
	{
		Player->ScreamReaction(this);
	}
}

void ASecondBossEnemy::EndScreamAttack()
{
	bScreamAttack=false;
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(ScreamTimer);
	}
}

