// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/SecondBoss/SecondBossEnemy.h"

#include "FirstStageSecondBossComponent.h"
#include "HealthComponent.h"
#include "NiagaraComponent.h"
#include "SecondBossEnemyAIController.h"
#include "SecondStageSecondBossComponent.h"
#include "ThirdStageSecondBossComponent.h"

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
			break;
		}
	case Second:
		{
			BehaviorTreeAsset=SecondStageSecondBossComponent->GetBehaviorTree();
			SecondBossEnemyAIController->ChangeBTStage();
			SecondStageAction();
			break;
		}
	case Third:
		{
			BehaviorTreeAsset=ThirdStageSecondBossComponent->GetBehaviorTree();
			SecondBossEnemyAIController->ChangeBTStage();
			ThirdStageAction();
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
	const ESecondBossStages NextStage = static_cast<ESecondBossStages>(static_cast<uint8>(CurrentStage) + 1);
	ChangeStage(NextStage);
}

void ASecondBossEnemy::StartBoss()
{
	CurrentStage=First;
	ChangeStage(CurrentStage);
}

void ASecondBossEnemy::SecondStageAction()
{
	
}

void ASecondBossEnemy::ThirdStageAction()
{
	
}

