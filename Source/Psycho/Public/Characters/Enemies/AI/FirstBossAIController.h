// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/AI/BaseEnemyAIController.h"
#include "FirstBossAIController.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API AFirstBossAIController : public ABaseEnemyAIController
{
	GENERATED_BODY()
protected:
	virtual bool GetCanFocus() const override;
};
