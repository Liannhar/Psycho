// Fill out your copyright notice in the Description page of Project Settings.


#include "Plots/PlotActor.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"

// Sets default values
APlotActor::APlotActor()
{
	PrimaryActorTick.bCanEverTick = false;
	BoxComponent=CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxComponent->SetBoxExtent(FVector(32.0f,32.0f,32.0f));
}

void APlotActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlotActor::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(Cast<APlayerCharacter>(OtherActor) && !WasOverlap)
	{
		WasOverlap=true;
		PlayDialog(OtherActor);	
	}
}

void APlotActor::PlayDialog(AActor*& NeededOwner)
{
	const auto World = GetWorld();
	if(SoundWaves.Num()>CurrentIndex && World ){
		const auto SoundWave = SoundWaves[CurrentIndex];
		if(NeedOwner)
		{
			UGameplayStatics::PlaySound2D(World,SoundWave,1,1,0,nullptr,NeededOwner);
		}
		else
		{
			UGameplayStatics::PlaySound2D(World,SoundWave);
		}
		CurrentIndex++;
		PlayDialog(NeededOwner);
	}
}



