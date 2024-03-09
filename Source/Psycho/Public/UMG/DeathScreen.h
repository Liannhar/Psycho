// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeathScreen.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UDeathScreen : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float DesaturationScale;

	UFUNCTION(BlueprintCallable)
    void SetDesaturationScale(const float NewValue) { DesaturationScale = NewValue; };
};
