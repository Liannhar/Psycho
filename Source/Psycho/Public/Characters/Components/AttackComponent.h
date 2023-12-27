// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoreTypes.h"
#include "Psycho/CoreTypes.h"
#include "AttackComponent.generated.h"

class ABaseCharacter;
struct FCombination;
class ABaseWeapon;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttackComponent();
	void StartAttack(EComboInput Input);
	void EndAttack();
	void SetNextAttack(bool CanAttack){CanAttackNext=CanAttack;}
	void SetTimeAttack(bool CanAttack){CantAttackInTime=CanAttack;}
	void SetCombo();
	void SetAttackDirection(const FVector2D& NewVector){AttackDirection=NewVector;}
	void SetForwardDirection(const FVector& NewVector){ForwardDirection=NewVector;}
	void SetRightDirection(const FVector& NewVector){RightDirection=NewVector;}
	void Damage() const;
	int32 GetAttackIndex() const {return AttackIndex;}

protected:
	virtual void BeginPlay() override;
	TArray<FCombination> Combos;

	UPROPERTY(EditAnywhere,Category="Attack")
	float RotationSpeed = 50.0f;
	UPROPERTY(EditAnywhere,Category="Attack")
	float LengthLineAttack=100.0f;
	UPROPERTY(EditAnywhere,Category="Attack")
	float SphereDamageRadius=30.0f;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	ABaseCharacter* GetCharacter() const;
	ABaseWeapon* GetWeapon() const;
	
	int32 AttackIndex = 0;
	int32 CurrentComboAttack = 0;
	bool CanAttackNext = false;
	bool CantAttackInTime = true;
	FTimerHandle TimerEndAnimMontage;
	
	void ActiveAttack(FCombination Attack);
	void AttackTarget() const;

	FVector2D AttackDirection=FVector2d(0.0f,0.0f);
	FVector ForwardDirection;
	FVector RightDirection;
	
	
	EComboInput CurrentComboInput= None;

	float RotationAngle(const ABaseCharacter* BaseCharacter) const;
};
