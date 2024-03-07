// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBoxes/Components/FarmaTriggerComponent.h"

#include "StartFightActor.h"

void UFarmaTriggerComponent::Interact(AActor* OtherActor)
{
	Super::Interact(OtherActor);
	if(TriggeredStartFightActor)
	{
		TriggeredStartFightActor->ActionStartFightActor(OtherActor);
	}
}
