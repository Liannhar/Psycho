// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/Components/ThirdStageSecondBossComponent.h"

#include "SecondBossEnemy.h"

UThirdStageSecondBossComponent::UThirdStageSecondBossComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UThirdStageSecondBossComponent::BeginPlay()
{
	Super::BeginPlay();
	SecondBoss = Cast<ASecondBossEnemy>(GetOwner());
}

void UThirdStageSecondBossComponent::ThirdStageStartAction()
{
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(ActionTimer,this,&UThirdStageSecondBossComponent::EndThirdStage,ActionTime);
	}
}

void UThirdStageSecondBossComponent::EndThirdStage()
{
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(ActionTimer);
	}
	SecondBoss->EndStage();
}


