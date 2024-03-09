// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TutorialWidgetComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnTutorialClosed);

struct FInputActionValue;

enum class EGameInputMode : uint8 {
     GAME_UI = 0,
     GAME = 1,
     UI = 2,
     UNKNOWN = 3
};

UCLASS( Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UTutorialWidgetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTutorialWidgetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void CloseTutorialWidget(const FInputActionValue& Value);
	EGameInputMode GetCurrentViewMode(const APlayerController *PlayerController);

	class UTutorialWidget* TutorialWidget;

	bool isGamePaused;
	bool isModeGameOnly;
	bool hasBeenShown;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	virtual void ShowTutorial();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Tutorial Data")
	FText Name;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Tutorial Data")
	class UMaterial* ImageMaterial;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Tutorial Data", meta = (MultiLine = true))
	FText Description;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Tutorial Data")
	TSubclassOf<class UTutorialWidget> TutorialWidgetClass;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tutorial Data")
	class UInputMappingContext* TutorialInputMappingContext;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tutorial Data")
    class UInputAction* CloseWidgetAction;

	FOnTutorialClosed TutorialClosed;
};
