// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/PillsComponent.h"
#include "Pills/BasePills.h"
#include "Structures/PillsDataStructure.h"

// Sets default values for this component's properties
UPillsComponent::UPillsComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPillsComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UPillsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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

	if (UBasePills* PillToTake = NewObject<UBasePills>(this, PillStack.Last()))
	{
		PillToTake->UsePill();
		PillStack.RemoveAt(PillStack.Num() - 1);
		OnPillUsed.Broadcast(PillToTake);
	}
}


bool UPillsComponent::IsPillEffectActive()
{
	return GetWorld()->GetTimerManager().IsTimerActive(PillPositiveEffectsTimer) || GetWorld()->GetTimerManager().IsTimerActive(PillNegativeEffectsTimer);
}
