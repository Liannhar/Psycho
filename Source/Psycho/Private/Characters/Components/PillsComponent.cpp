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
