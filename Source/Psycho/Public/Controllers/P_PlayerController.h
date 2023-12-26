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
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UPlayerInputActions* InputActions;

	UPROPERTY()
	class APlayerCharacter* PlayerCharacter;
	
protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Sprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	void SlowWalk(const FInputActionValue& Value);
	void StopSlowWalk(const FInputActionValue& Value);
	void LightAttack(const FInputActionValue& Value);
	void HeavyAttack(const FInputActionValue& Value);
	void TakePill(const FInputActionValue& Value);

	UAttackComponent* GetAttackComponent() const;
};

