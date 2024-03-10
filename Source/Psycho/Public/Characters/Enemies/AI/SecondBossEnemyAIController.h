// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/AI/BaseEnemyAIController.h"
#include "SecondBossEnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API ASecondBossEnemyAIController : public ABaseEnemyAIController
{
	GENERATED_BODY()
public:
	void ChangeBTStage();
};
