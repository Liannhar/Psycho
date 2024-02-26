// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PillsComponent.generated.h"

class UBasePills;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPillAddedDelegate, TSubclassOf<UBasePills>, AddedPill);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPillUsedDelegate, UBasePills*, UsedPill);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBlurringStartDelegate, const float&, BlurStrength);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FPillChanged, const int&, CurrentPill);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBlurringEndDelegate);

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

	uint8 CurrentPillIndex;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
	UPROPERTY(BlueprintAssignable)
	FPillAddedDelegate OnPillAdded;
	UPROPERTY(BlueprintAssignable)
	FPillUsedDelegate OnPillUsed;
	UPROPERTY(BlueprintAssignable)
	FBlurringStartDelegate OnBlurringStart;
	UPROPERTY(BlueprintAssignable)
	FBlurringEndDelegate OnBlurringEnd;
	UPROPERTY(BlueprintAssignable)
	FPillChanged OnPillChanged;

	void AddPill(class UPillsDataStructure* PillData);
	void TakePill();
	void SetPillEffectsTimer(FTimerHandle& Timer) { PillPositiveEffectsTimer = Timer;};
	void SetPillAfterEffectsTimer(FTimerHandle& Timer) { PillNegativeEffectsTimer = Timer;};
	void SetCurrentPillIndex(int NewCurrentPIllIndex);
	bool IsPillEffectActive();

	UFUNCTION(BlueprintCallable)
	uint8 GetCurrentPillIndex() { return CurrentPillIndex; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Pills)
	TArray<TSubclassOf<UBasePills>> PillStack;	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pills)
	FTimerHandle PillPositiveEffectsTimer;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pills)
	FTimerHandle PillNegativeEffectsTimer;
};
