// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "P_PlayerController.generated.h"

class UAttackComponent;
DECLARE_MULTICAST_DELEGATE_OneParam(FOnMoveSignature,FVector2d); 

/**
 * 
 */
UCLASS()
class PSYCHO_API AP_PlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* TargetOnMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	class UPlayerInputActions* InputActions;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;

	// Movement system
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float DefaultWalkSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float SprintSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float SlowWalkSpeed;

	bool bIsSprinting;
	bool bIsSlowWalking;

	// Target System
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target System", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float LockOnDistance;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target System", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float LockOnRadius;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target System", meta = (AllowPrivateAccess = "true"))
	FVector CameraLockedOnOffset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target System", meta = (AllowPrivateAccess = "true"))
	float ChangeTargetAtMouseSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target System", meta = (AllowPrivateAccess = "true"))
	float BoxTraceWidth;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target System", meta = (AllowPrivateAccess = "true"))
	float BoxTraceLength;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target System", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float RotationSpeed;

	AActor* LockedOnTarget;
	bool bIsLockedOnTarget;
	FVector CameraDefaultLocation;
public:
	UFUNCTION(BlueprintCallable)
	bool GetLockOnTarget() const {return bIsLockedOnTarget;}
	AActor* GetLockedOnTarget() const {return LockedOnTarget;}

	// Movement
	void Sprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	void DodgeSprint(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;

	// Movement
	void Move(const FInputActionValue& Value);
	
	void SlowWalk(const FInputActionValue& Value);
	void StopSlowWalk(const FInputActionValue& Value);
	
	// Look
	void Look(const FInputActionValue& Value);

	// Attacks
	void LightAttack(const FInputActionValue& Value);
	void HeavyAttack(const FInputActionValue& Value);

	// Pill
	void TakePill(const FInputActionValue& Value);
	UAttackComponent* GetAttackComponent() const;

	// Target System
	void LockOnTarget(const FInputActionValue& Value);
	void ChangeTargetOn(const FInputActionValue& Value);
	AActor* FindTargetToChange(const FVector& Direction); 

	//Interact
	void Interact(const FInputActionValue& Value);

	// Dodge
	void Dodge(const FInputActionValue& Value);

public:
	AP_PlayerController();
};

