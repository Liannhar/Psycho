// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TutorialWidget.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UTutorialWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* Name;
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class URichTextBlock* Description;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UImage* Showcase;
};
