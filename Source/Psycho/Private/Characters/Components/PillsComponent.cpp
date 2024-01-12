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

	// // For testing purpose
	// UBasePills* NewPill = NewObject<UBasePills>();
	// AddPill(NewPill);
	// NewPill = NewObject<UBasePills>();
	// AddPill(NewPill);
	
}


// Called every frame
void UPillsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UPillsComponent::AddPill(UPillsDataStructure* PillData)
{
	UClass* PillType = PillData->GetPillType();
	UBasePills* NewPill = NewObject<UBasePills>(this, PillType);
	
	if (!NewPill) return;

	NewPill->Init(PillData);
	PillsStack.Add(NewPill);
	OnPillAdded.Broadcast(NewPill);
}

void UPillsComponent::TakePill()
{
	if (PillsStack.IsEmpty()) 
	{
		if(GEngine)
     		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("No pills"));
		return;
	}

	UBasePills* PillToTake = PillsStack.Last();

	if (PillToTake)
	{
		PillToTake->UsePill();
		OnPillUsed.Broadcast(PillToTake);
		PillsStack.Remove(PillToTake);
	}
}
