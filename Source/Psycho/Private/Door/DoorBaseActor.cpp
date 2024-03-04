// Fill out your copyright notice in the Description page of Project Settings.


#include "Door/DoorBaseActor.h"

ADoorBaseActor::ADoorBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ADoorBaseActor::BeginPlay()
{
	Super::BeginPlay();
	
}

