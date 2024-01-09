// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/StartFightActor.h"

#include "Components/BoxComponent.h"
#include "Player/PlayerCharacter.h"
#include "Psycho/PsychoGameModeBase.h"

AStartFightActor::AStartFightActor()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent=CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->SetBoxExtent(FVector(100.0f,100.0f,50.0f));
}

void AStartFightActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AStartFightActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(Cast<APlayerCharacter>(OtherActor) && !FightWasStarted)
	{
		FightWasStarted=true;
		if(const auto GameMode = Cast<APsychoGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->SetFightStatus(true);
		}
	}
}

