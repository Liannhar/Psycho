#pragma once
 
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "InputAction.h"
#include "PlayerInputActions.generated.h"
 
/**
 * Store pointer to Input Action for native binding
*/
UCLASS()
class PSYCHO_API UPlayerInputActions : public UDataAsset
{
    GENERATED_BODY()
 
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* MoveAction;
 
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* LookAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* SprintAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* SlowWalkAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* LightAttackAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* HeavyAttackAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* TakePillAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* LockOnTargetAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* ChangeTargetOnAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UInputAction* Interact;
};