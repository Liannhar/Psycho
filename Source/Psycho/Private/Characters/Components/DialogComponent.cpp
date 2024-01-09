// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/DialogComponent.h"

#include "Kismet/GameplayStatics.h"
#include "Player/PlayerCharacter.h"
#include "Sound/DialogueWave.h"

UDialogComponent::UDialogComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}
void UDialogComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UDialogComponent::PlayDialog(FName Name)
{
	const auto World = GetWorld();
	const auto DialogueWave = DialogueWaves[Name];
	if(DialogueWave && World && GetOwner())
	{
		
		UGameplayStatics::PlaySound2D(World,SoundWave);
	}
}


