// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "InputActionValue.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PSYCHO_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

private:
	/** Camera boom positioning the camera behind the character */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Pills, meta = (AllowPrivateAccess = "true"))
	class UPillsComponent* PillsComponent;
	

	void EndStunPlayer();

	FTimerHandle StunTimerHandle;

	
protected:
	void LoadGame();
	virtual void BeginPlay() override;
public:
	APlayerCharacter();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	FORCEINLINE class UPillsComponent* GetPillsComponent() const { return PillsComponent; }

	void StartStunPlayer(float TimeStun);

	UPROPERTY(EditAnywhere,Category="Dodge")
	UAnimMontage* DodgeRight;
	UPROPERTY(EditAnywhere,Category="Dodge")
	UAnimMontage* DodgeLeft;
	UPROPERTY(EditAnywhere,Category="Dodge")
	UAnimMontage* DodgeForward;
};
