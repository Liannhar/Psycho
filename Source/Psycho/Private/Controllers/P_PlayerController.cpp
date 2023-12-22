// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/P_PlayerController.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Characters/Player/PlayerCharacter.h"
#include "DataAssets\PlayerInputActions.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"


AP_PlayerController::AP_PlayerController()
{
	PrimaryActorTick.bCanEverTick = true;

	CameraLockedOnOffset = FVector(0.f, 0.f, 100.f);

	ChangeTargetAtMouseSpeed = 1.f;
	BoxTraceWidth = 500.f;
	BoxTraceLength = 1000.f;
}


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

	bIsLockedOnTarget = false;
	PlayerCharacter->GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
	CameraDefaultLocation = PlayerCharacter->GetCameraBoom()->GetRelativeLocation();
	CameraLockedOnOffset += CameraDefaultLocation;
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

		// Pill
		EnhancedInputComponent->BindAction(InputActions->TakePillAction, ETriggerEvent::Triggered, this, &AP_PlayerController::TakePill);
		
		// Lock On Target
		EnhancedInputComponent->BindAction(InputActions->LockOnTargetAction, ETriggerEvent::Triggered, this, &AP_PlayerController::LockOnTarget);
		EnhancedInputComponent->BindAction(InputActions->ChangeTargetOnAction, ETriggerEvent::Triggered, this, &AP_PlayerController::ChangeTargetOn);
	}
}


void AP_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bIsLockedOnTarget && LockedOnTarget)
	{
		FVector InterCameraBoomLocation = FMath::VInterpTo(PlayerCharacter->GetCameraBoom()->GetRelativeLocation(), CameraLockedOnOffset, DeltaSeconds, 5.f);
		PlayerCharacter->GetCameraBoom()->SetRelativeLocation(InterCameraBoomLocation);

		FRotator LookAtTarget = UKismetMathLibrary::FindLookAtRotation(PlayerCharacter->GetActorLocation(), LockedOnTarget->GetActorLocation());
		FRotator Interpolation = FMath::RInterpTo(GetControlRotation(), LookAtTarget, DeltaSeconds, 5);
		SetControlRotation(Interpolation/* FRotator(Interpolation.Pitch, Interpolation.Yaw, GetControlRotation().Roll) */);
	} else {
		FVector InterCameraBoomLocation = FMath::VInterpTo(PlayerCharacter->GetCameraBoom()->GetRelativeLocation(), CameraDefaultLocation, DeltaSeconds, 15.f);
		PlayerCharacter->GetCameraBoom()->SetRelativeLocation(InterCameraBoomLocation);
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
	if (bIsLockedOnTarget) return;

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


void AP_PlayerController::LockOnTarget(const FInputActionValue& Value)
{
	if (!PlayerCharacter) return;

	if (bIsLockedOnTarget)
	{
		bIsLockedOnTarget = false;
		PlayerCharacter->bUseControllerRotationYaw = false;

		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Subsystem->RemoveMappingContext(TargetOnMappingContext);
		}

		return;
	}

	FVector Start = PlayerCharacter->GetActorLocation();
	FVector X = FVector(PlayerCharacter->GetFollowCamera()->GetForwardVector().X, PlayerCharacter->GetFollowCamera()->GetForwardVector().Y, 0);
	FVector End = LockOnDistance * X + PlayerCharacter->GetActorLocation();
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(PlayerCharacter);
	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	bool Hit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, LockOnRadius, ObjectTypesArray, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true);

	if (!Hit) return;

	bIsLockedOnTarget = true;
	PlayerCharacter->bUseControllerRotationYaw = true;
	LockedOnTarget = HitResult.GetActor();

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(TargetOnMappingContext, 0);
	}
}


AActor* AP_PlayerController::FindTargetToChange(const FVector& Direction)
{
	// What kind of objects do we want to consider. Currently - Pawns
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	// Containing hit results per Pawn we hit by trace
	TArray<FHitResult> HitResults;

	// List of actors to ignore when traicing. Currently - Player and LockedOnTarget
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(LockedOnTarget);
	ActorsToIgnore.Add(PlayerCharacter);

	// Size of the box that hits Pawns
	FVector BoxSize = FVector();

	// In BoxTraceStart pushing forward BoxTrace to not check Pawns that are behind Player
	FVector BoxTraceStart = PlayerCharacter->GetActorLocation() + PlayerCharacter->GetActorForwardVector() * BoxTraceWidth;
	FVector BoxTraceEnd =  BoxTraceStart + Direction * BoxTraceLength;

	bool HitTrace = UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetWorld(), 
		BoxTraceStart, 
		BoxTraceEnd, 
		FVector(1.f, BoxTraceWidth, 50.f), 
		UKismetMathLibrary::MakeRotFromX(Direction), 
		ObjectTypesArray, 
		false, 
		ActorsToIgnore, 
		EDrawDebugTrace::ForDuration, 
		HitResults, 
		true
		);

	// Variable to determine the minimal Angle between PlayerForwardVector and Pawn
	// Since maximum angle is 360 then in radian it will be 2𝝿 wich is 6,28319
	float MinAngle = 10;
	AActor* NewTarget = nullptr;

	// Going through all Pawn (Enemies) that were hited to find new target
	for (FHitResult Hit : HitResults)
	{
		// To normalize Pawn (Enemy) location we should firstly use GetSafeNormal funciton and then Normalize
		FVector NormalizedEnemyLocation = (Hit.GetActor()->GetActorLocation() - PlayerCharacter->GetActorLocation()).GetSafeNormal();
		NormalizedEnemyLocation.Normalize();

		// Angle in radians between Pawn (Enemy) and Player
		float PlayerEnemyAngle = FMath::Acos(FVector::DotProduct(PlayerCharacter->GetActorForwardVector(), NormalizedEnemyLocation));

		// Drawing spheres on Pawns that were hited by BoxTrace
		UKismetSystemLibrary::DrawDebugSphere(GetWorld(), Hit.GetActor()->GetActorLocation(), 100.f, 12, FLinearColor::White, 5, 1.f);

		// Updating NewTarget and MinAngle when found lower angle between Player and Pawn
		if (PlayerEnemyAngle < MinAngle)
		{
			NewTarget = Hit.GetActor();
			MinAngle = PlayerEnemyAngle;
		}
	}

	return NewTarget;
}


void AP_PlayerController::ChangeTargetOn(const FInputActionValue& Value)
{
	// Getting X input of a mouse to know at what direction Player is trying to change target
	float MouseInputX = Value.Get<FVector>().X;

	// Checking if Player trying to change target thats on the right. X input is positive when moving right
	bool bRight = MouseInputX > 0;

	if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("MouseInputX: %f"), MouseInputX));
	
	// if absolute value of X input is greater than speed treshhold then change target
	if (fabs(MouseInputX) >= ChangeTargetAtMouseSpeed)
	{
		AActor* NewTarget = FindTargetToChange(PlayerCharacter->GetActorRightVector() * (bRight ? 1 : -1));
		
		LockedOnTarget = NewTarget ? NewTarget : LockedOnTarget;
	}
}
