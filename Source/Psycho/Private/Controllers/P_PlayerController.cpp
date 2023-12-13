// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/P_PlayerController.h"
#include "Components/InputComponent.h"
#include "Characters/Player/PlayerCharacter.h"
#include "DataAssets\PlayerInputActions.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void AP_PlayerController::BeginPlay()
{
	PlayerCharacter = Cast<APlayerCharacter>(GetPawn());

	if (!PlayerCharacter)
	{
		// TODOD: Spawn APlayerCharacter using save data
		// Pseudocode: Spawn<APlayerCharacter>().SetLocatoin(SaveData->PlayerCharacterLocation)
		return;
	}

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->ClearAllMappings();
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}

	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
}

void AP_PlayerController::SetupInputComponent() 
{
	Super::SetupInputComponent();

	if (!InputActions) return;

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent)) 
	{
		EnhancedInputComponent->BindAction(InputActions->MoveAction, ETriggerEvent::Triggered, this, &AP_PlayerController::Move);
		EnhancedInputComponent->BindAction(InputActions->LookAction, ETriggerEvent::Triggered, this, &AP_PlayerController::Look);

		// Sprint
		EnhancedInputComponent->BindAction(InputActions->SprintAction, ETriggerEvent::Started, this, &AP_PlayerController::Sprint);
		EnhancedInputComponent->BindAction(InputActions->SprintAction, ETriggerEvent::Completed, this, &AP_PlayerController::StopSprint);

		// SlowWalk
		EnhancedInputComponent->BindAction(InputActions->SlowWalkAction, ETriggerEvent::Started, this, &AP_PlayerController::SlowWalk);
		EnhancedInputComponent->BindAction(InputActions->SlowWalkAction, ETriggerEvent::Completed, this, &AP_PlayerController::StopSlowWalk);

		// Attacks
		EnhancedInputComponent->BindAction(InputActions->LightAttackAction, ETriggerEvent::Triggered, this, &AP_PlayerController::LightAttack);
		EnhancedInputComponent->BindAction(InputActions->HeavyAttackAction, ETriggerEvent::Triggered, this, &AP_PlayerController::HeavyAttack);

		EnhancedInputComponent->BindAction(InputActions->TakePillAction, ETriggerEvent::Triggered, this, &AP_PlayerController::TakePill);
	}
}

void AP_PlayerController::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();
    
	// find out which way is forward
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	if (PlayerCharacter) 
	{
		PlayerCharacter->AddMovementInput(ForwardDirection, MovementVector.Y);
		PlayerCharacter->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AP_PlayerController::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	// add yaw and pitch input to controller
	if (PlayerCharacter) 
	{
		PlayerCharacter->AddControllerYawInput(LookAxisVector.X);
		PlayerCharacter->AddControllerPitchInput(-LookAxisVector.Y);
	}
}

void AP_PlayerController::Sprint(const FInputActionValue& Value)
{
	bIsSprinting = true;
	bIsSlowWalking = false;

	if (PlayerCharacter) 
	{
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	}

	if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Sprint!"));
}


void AP_PlayerController::StopSprint(const FInputActionValue& Value)
{
	bIsSprinting = false;

	if (PlayerCharacter && !bIsSlowWalking) 
	{
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	}

	if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Stop Sprint!"));
}


void AP_PlayerController::SlowWalk(const FInputActionValue& Value)
{
	bIsSlowWalking = true;
	bIsSprinting = false;

	if (PlayerCharacter) 
	{
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = SlowWalkSpeed;
	}

	if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Slow Walk!"));
}


void AP_PlayerController::StopSlowWalk(const FInputActionValue& Value)
{
	bIsSlowWalking = false;

	if (PlayerCharacter && !bIsSprinting) 
	{
		PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	}
	
	if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Stop Slow Walk!"));
}


void AP_PlayerController::LightAttack(const FInputActionValue& Value)
{
	// TODO: LightAttack Logic
	if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Light Attack!"));	
}

void AP_PlayerController::HeavyAttack(const FInputActionValue& Value)
{
	// TODO: HeavyAttack Logic
	if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Heavy Attack!"));	
}

void AP_PlayerController::TakePill(const FInputActionValue& Value)
{
	// TODO: TakePill Logic
	if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Taking a Pill!"));	
}
