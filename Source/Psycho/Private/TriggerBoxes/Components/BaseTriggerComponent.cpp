// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBoxes/Components/BaseTriggerComponent.h"

UBaseTriggerComponent::UBaseTriggerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UBaseTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UBaseTriggerComponent::Interact(AActor* OtherActor)
{
	
}
