// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem/InventoryComponent.h"

#include "InventorySystem/Item.h"


// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	for (const auto& Item : DefaultItems)
	{
		AddItem(Item);
	}
}



// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::AddItem(TSubclassOf<UItem> Item)
{
	Items.Add(Item);
	OnInventoryUpdated.Broadcast();
}

bool UInventoryComponent::RemoveItem(TSubclassOf<UItem> Item)
{
	if (Item == nullptr)
	{
		return false;
	}
	Items.RemoveSingle(Item);
	OnInventoryUpdated.Broadcast();
	return true;
}

