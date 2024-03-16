// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/StartFightActor.h"
#include "FirstBossStartFightActor.generated.h"

class AFirstBossEnemy;
/**
 * 
 */
UCLASS()
class PSYCHO_API AFirstBossStartFightActor : public AStartFightActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Boss")
	AFirstBossEnemy* FirstBoss;
};
