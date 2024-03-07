// Fill out your copyright notice in the Description page of Project Settings.


#include "Pills/FarmaPillActor.h"

#include "Components/FarmaTriggerComponent.h"

AFarmaPillActor::AFarmaPillActor()
{
	FirmaTriggerComponent = CreateDefaultSubobject<UFarmaTriggerComponent>("Trigger Component");

}
