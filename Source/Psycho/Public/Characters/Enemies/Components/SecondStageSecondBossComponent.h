// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SecondStageSecondBossComponent.generated.h"


class UBehaviorTree;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API USecondStageSecondBossComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USecondStageSecondBossComponent();

protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="FirstStage")
	UBehaviorTree* SecondStageBehaviorTreeAsset;

public:
	UBehaviorTree* GetBehaviorTree() const {return SecondStageBehaviorTreeAsset;}
};
