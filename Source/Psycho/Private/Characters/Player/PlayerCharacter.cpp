// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Player/PlayerCharacter.h"

#include "BaseEnemy.h"
#include "Characters/Components/PillsComponent.h"

#include "BaseWeapon.h"
#include "HealthComponent.h"
#include "MotionWarpingComponent.h"
#include "PsychoSaveGame.h"
#include "P_PlayerController.h"
#include "WeaponComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Psycho/PsychoGameModeBase.h"
#include "UMG/DeathScreen.h"
#include "Blueprint/UserWidget.h"


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

	DeathScreenClass = nullptr;
	DeathScreen = nullptr;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	//LoadGame();

	HealthComponent->OnDeath.AddDynamic(this, &APlayerCharacter::ShowDeathScreen);
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

void APlayerCharacter::StartStunPlayer(const float& TimeStun)
{
	const auto PlayerController = Cast<AP_PlayerController>(GetController());
	if(!PlayerController) return;
	PlayerController->DisableInput(PlayerController);
	
	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().SetTimer(StunTimerHandle,this,&APlayerCharacter::EndStunPlayer,TimeStun);
}

void APlayerCharacter::ScreamReaction(ASecondBossEnemy*&& SecondBossEnemy) const
{
	FVector Direction = GetActorLocation()-SecondBossEnemy->GetActorLocation();
	Direction.Normalize();
	const FRotator Rotation = Direction.Rotation();
	const float DotProduct = FVector::DotProduct(GetActorForwardVector(),SecondBossEnemy->GetActorForwardVector());
	const int32 Angle = DotProduct>0?1:-1;
	const FVector NewLocation = FVector(GetActorLocation().X+Angle*Rotation.Yaw*100.0f,GetActorLocation().Y+Angle*Rotation.Yaw*100.0f,GetActorLocation().Z);

	//MotionWarpingComponent->AddOrUpdateWarpTargetFromLocation("ScreamReaction",NewLocation);	
	//PlayAnimMontage(ScreamReactionMontage);
}

void APlayerCharacter::GetDamage(AActor* Actor)
{
	Super::GetDamage(Actor);
	auto AttackDirection = 0;
	auto DistanceOfRepulsion = 0.0f;
	if(const auto Enemy = Cast<ABaseEnemy>(Actor))
	{
		AttackDirection = Enemy->GetAttackComponent()->GetCurrentAttackDirection();
		DistanceOfRepulsion = Enemy->GetAttackComponent()->GetCurrentAttackRepulsion();
	}
	FVector NewLocation;
	
	if(AttackDirection!=0)
	{	
		NewLocation = FVector(GetActorLocation().X+GetActorRightVector().X*AttackDirection*DistanceOfRepulsion*10.0f,GetActorLocation().Y+GetActorRightVector().Y*AttackDirection*DistanceOfRepulsion*10.0f,GetActorLocation().Z);
	}
	else
	{
		NewLocation = GetActorLocation()+(GetActorForwardVector()+Actor->GetActorForwardVector())*DistanceOfRepulsion;
	}
	SetActorLocation(NewLocation);
}


void APlayerCharacter::EndStunPlayer()
{
	const auto PlayerController = Cast<AP_PlayerController>(GetController());
	if(!PlayerController) return;
	PlayerController->EnableInput(PlayerController);
	if(!GetWorld()) return;
	GetWorld()->GetTimerManager().ClearTimer(StunTimerHandle);
}

void APlayerCharacter::ShowDeathScreen(ABaseCharacter* Character)
{
	if (DeathScreenClass && !DeathScreen)
	{
		const auto PlayerController = Cast<AP_PlayerController>(GetController());
		check(PlayerController);
		DeathScreen = CreateWidget<UDeathScreen>(PlayerController, DeathScreenClass);
		check(DeathScreen);
		DeathScreen->AddToPlayerScreen();
	}
}