// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBoxes/BaseTriggerBox.h"

#include "Components/BoxComponent.h"
#include "Player/PlayerCharacter.h"

ABaseTriggerBox::ABaseTriggerBox()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent=CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->SetBoxExtent(FVector(100.0f,100.0f,50.0f));
}

void ABaseTriggerBox::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseTriggerBox::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(Cast<APlayerCharacter>(OtherActor))
	{
		Action();
		End();
	}
	
}

void ABaseTriggerBox::Action()
{
}

void ABaseTriggerBox::End()
{
	Destroy();
}



