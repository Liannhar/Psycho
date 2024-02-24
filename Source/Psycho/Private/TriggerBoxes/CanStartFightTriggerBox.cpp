// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBoxes/CanStartFightTriggerBox.h"

#include "StartFightActor.h"

void ACanStartFightTriggerBox::Action()
{
	Super::Action();
	if(StartFightActor)
	{
		StartFightActor->ChangeNeedTrigger(false);
	}
}
