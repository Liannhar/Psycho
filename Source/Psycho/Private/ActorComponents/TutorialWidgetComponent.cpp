// Fill out your copyright notice in the Description page of Project Settings.


#include "ActorComponents/TutorialWidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "MediaPlayer.h"
#include "MediaTexture.h"
#include "UMG/TutorialWidget.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"
#include "Components/TextBlock.h"
#include "Materials/Material.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/P_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"

// Sets default values for this component's properties
UTutorialWidgetComponent::UTutorialWidgetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	hasBeenShown = false;
}


// Called when the game starts
void UTutorialWidgetComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTutorialWidgetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTutorialWidgetComponent::ShowTutorial()
{
	if (hasBeenShown) return;

	if (AP_PlayerController* PlayerController = Cast<AP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		isGamePaused = UGameplayStatics::IsGamePaused(GetWorld());
		UGameplayStatics::SetGamePaused(GetWorld(), !isGamePaused);

		isModeGameOnly = GetCurrentViewMode(PlayerController) == EGameInputMode::GAME;
		if (isModeGameOnly)
			PlayerController->SetInputMode(FInputModeGameAndUI());

		PlayerController->bShowMouseCursor = true;

		check(TutorialInputMappingContext);
		PlayerController->AddInputMappingContext(TutorialInputMappingContext);

		check(CloseWidgetAction);
		if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerController->InputComponent)) 
		{
			EnhancedInputComponent->BindAction(CloseWidgetAction, ETriggerEvent::Triggered, this, &UTutorialWidgetComponent::CloseTutorialWidget);
		}

		check(TutorialWidgetClass);
		TutorialWidget = CreateWidget<UTutorialWidget>(PlayerController, TutorialWidgetClass);

		check(TutorialWidget);
		TutorialWidget->Showcase->SetBrushFromMaterial(ImageMaterial);
		TutorialWidget->Name->SetText(Name);
		TutorialWidget->Description->SetText(Description);
		TutorialWidget->AddToViewport(10);

		hasBeenShown = true;
	}
}


void UTutorialWidgetComponent::CloseTutorialWidget(const FInputActionValue& Value)
{
	if (AP_PlayerController* PlayerController = Cast<AP_PlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0)))
	{
		UGameplayStatics::SetGamePaused(GetWorld(), isGamePaused);

		if (isModeGameOnly)
			PlayerController->SetInputMode(FInputModeGameOnly());
		
		PlayerController->bShowMouseCursor = false;
		PlayerController->RemoveInputMappingContext(TutorialInputMappingContext);

		TutorialWidget->RemoveFromParent();
w		TutorialClosed.Broadcast();
	}
}


EGameInputMode UTutorialWidgetComponent::GetCurrentViewMode(const APlayerController *PlayerController)
{
    if (PlayerController)
    {
        UGameViewportClient* GameViewportClient = PlayerController->GetWorld()->GetGameViewport();
        ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();

        bool Ignore = GameViewportClient->IgnoreInput();
        EMouseCaptureMode MouseCaptureMide = GameViewportClient->GetMouseCaptureMode();

        if (Ignore == false && MouseCaptureMide == EMouseCaptureMode::CaptureDuringMouseDown)
        {
            return EGameInputMode::GAME_UI;  // Game And UI
        }
        else if (Ignore == true && MouseCaptureMide == EMouseCaptureMode::NoCapture)
        {
            return EGameInputMode::UI;  // UI Only
        }
        else
        {
            return EGameInputMode::GAME;  // Game Only
        }
    }

    return EGameInputMode::UNKNOWN;
}
