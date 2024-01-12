// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PillsComponent.generated.h"

class UBasePills;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPillAddedDelegate, UBasePills*, AddedPill);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPillUsedDelegate, UBasePills*, UsedPill);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UPillsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPillsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
	UPROPERTY(BlueprintAssignable)
	FPillAddedDelegate OnPillAdded;
	UPROPERTY(BlueprintAssignable)
	FPillUsedDelegate OnPillUsed;

	void AddPill(class UPillsDataStructure* PillData);
	void TakePill();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pills)
	TArray<UBasePills*> PillsStack;		
};
