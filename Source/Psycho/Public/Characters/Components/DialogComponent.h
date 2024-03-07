// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DialogComponent.generated.h"


class UDialogueVoice;
class UDialogueWave;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UDialogComponent : public UActorComponent
{
	GENERATED_BODY()
public:	
	UDialogComponent();
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere,Category="Dialogue")
	TMap<FName,UDialogueWave*> DialogueWaves;
	UPROPERTY(EditAnywhere,Category="Dialogue")
	UDialogueVoice* DialogueVoice;
	UPROPERTY(EditAnywhere,Category="Dialogue")
	USoundWave* SoundWave;
public:
	UFUNCTION(BlueprintCallable)
	void PlayDialog(FName& Name);
};
