// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SecondBossEnemy.h"
#include "Components/ActorComponent.h"
#include "ThirdStageSecondBossComponent.generated.h"


class UBehaviorTree;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UThirdStageSecondBossComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UThirdStageSecondBossComponent();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="FirstStage")
	UBehaviorTree* ThirdStageBehaviorTreeAsset;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="SecondStage")
	float ActionTime=100.0f;
	UPROPERTY()
	ASecondBossEnemy* SecondBoss;

private:
	FTimerHandle ActionTimer;

	void EndThirdStage();
	
public:
	UBehaviorTree* GetBehaviorTree() const {return ThirdStageBehaviorTreeAsset;}

	void ThirdStageStartAction();
	
};
