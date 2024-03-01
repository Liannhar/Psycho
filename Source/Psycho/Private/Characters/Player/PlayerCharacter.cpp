// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/PlayerCharacter.h"
#include "Characters/Components/PillsComponent.h"

#include "BaseWeapon.h"
#include "DialogComponent.h"
#include "HealthComponent.h"
#include "PsychoSaveGame.h"
#include "P_PlayerController.h"
#include "WeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "InventorySystem/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Psycho/PsychoGameModeBase.h"


APlayerCharacter::APlayerCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->bEnableCameraLag = true;
	CameraBoom->CameraLagSpeed = 10.0f;

	// Setting limitations to camera vertical view angle
	if (GetWorld())
	{
		if (APlayerCameraManager* CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0))
		{
			CameraManager->ViewPitchMax = 10.f;
			CameraManager->ViewPitchMin = -60.f;
		}
	}

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 

	PillsComponent = CreateDefaultSubobject<UPillsComponent>(TEXT("Pills Component"));
	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//LoadGame();
}

void APlayerCharacter::LoadGame()
{
	const auto GameMode = Cast<APsychoGameModeBase>(GetWorld()->GetAuthGameMode());
	if(GameMode)
	{
		const auto SaveGame = GameMode->GetCurrentSaveGame();
		if(SaveGame)
		{
			const auto PlayerSave = SaveGame->GetPlayerSave();
			SetActorLocation(PlayerSave.PlayerLocation);
			HealthComponent->SetMaxHP(PlayerSave.CurrentPlayerMaxHP);
			HealthComponent->SetCurrentHP(PlayerSave.CurrentPlayerHP);
			WeaponComponent->SetNewWeapon(PlayerSave.CurrentPlayerClassOfWeapon);
		}
	}
}

void APlayerCharacter::StartStunPlayer(float TimeStun)
{
	//здесь анимация стана

	const auto PlayerController = Cast<AP_PlayerController>(GetController());
	if(!PlayerController) return;
	PlayerController->DisableInput(PlayerController);
	
	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(StunTimerHandle,this,&APlayerCharacter::EndStunPlayer,TimeStun);
}

void APlayerCharacter::EndStunPlayer()
{
	const auto PlayerController = Cast<AP_PlayerController>(GetController());
	if(!PlayerController) return;
	PlayerController->EnableInput(PlayerController);
	//здесь вернуть idle
	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().ClearTimer(StunTimerHandle);
}