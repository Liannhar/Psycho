// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "EnemyAIPerceptionComponent.generated.h"

class ABaseEnemy;
/**
 * Receives other enemies, notices damage, player receives
 */
UCLASS()
class PSYCHO_API UEnemyAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	
	AActor* GetVisiblePlayer() const;
	TArray<ABaseEnemy*> GetVisibleEnemies() const;
	bool GetEnemyIsNotDamaged();
};
