// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PillsComponent.h"
#include "Pills/BasePills.h"
#include "Structures/PillsDataStructure.h"

// Sets default values for this component's properties
UPillsComponent::UPillsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UPillsComponent::BeginPlay()
{
	Super::BeginPlay();

}


void UPillsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


void UPillsComponent::AddPill(UPillsDataStructure* PillData)
{
	TSubclassOf<UBasePills> PillType = PillData->GetPillType();
	if (!PillType) return;

	PillStack.Add(PillType);
	OnPillAdded.Broadcast(PillType);
}

void UPillsComponent::TakePill()
{
	if (PillStack.IsEmpty())
	{
		if(GEngine)
     		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("No pills"));
		return;
	}

	if (UBasePills* PillToTake = NewObject<UBasePills>(this, PillStack[CurrentPillIndex]))
	{
		PillToTake->UsePill();
		PillStack.RemoveAt(CurrentPillIndex);
		SetCurrentPillIndex(CurrentPillIndex - 1);
		OnPillUsed.Broadcast(PillToTake);
	}
}


void UPillsComponent::SetCurrentPillIndex(int NewCurrentPIllIndex)
{
	if (PillStack.IsEmpty()) return;

	NewCurrentPIllIndex %= PillStack.Num();

	if (NewCurrentPIllIndex == 0)
	{
		CurrentPillIndex = 0;
	} 
	else if (NewCurrentPIllIndex > 0)
	{
		CurrentPillIndex = NewCurrentPIllIndex;
	} 
	else if (NewCurrentPIllIndex < 0)
	{
		CurrentPillIndex = PillStack.Num() + NewCurrentPIllIndex;
	}
	OnPillChanged.Broadcast(CurrentPillIndex);
}

bool UPillsComponent::IsPillEffectActive()
{
	return GetWorld()->GetTimerManager().IsTimerActive(PillPositiveEffectsTimer) || GetWorld()->GetTimerManager().IsTimerActive(PillNegativeEffectsTimer);
}
