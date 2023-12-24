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
DECLARE_MULTICAST_DELEGATE(FOnStartAttackSignature); 
DECLARE_MULTICAST_DELEGATE(FOnEndAttackSignature); 


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttackComponent();
	void StartAttack(EComboInput Input);
	void EndAttack();
	void SetNextAttack(bool CanAttack)
	{
		CanAttackNext=CanAttack;
		UE_LOG(LogTemp,Display,TEXT("AAAAAAAAAAAAA%d"),CanAttackNext?1:0);
	}
	void SetTimeAttack(bool CanAttack){CantAttackInTime=CanAttack;}
	void SetCombo();

	FOnStartAttackSignature OnStartAttack;
	FOnEndAttackSignature OnEndAttack;

protected:
	virtual void BeginPlay() override;
	TArray<FCombination> Combos;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	ABaseCharacter* GetCharacter() const;
	int32 AttackIndex = 0;
	int32 CurrentComboAttack = 0;
	bool CanAttackNext = false;
	bool CantAttackInTime = true;
	FTimerHandle TimerEndAnimMontage;
	ABaseWeapon* GetWeapon() const;
	void ActiveAttack(FCombination Attack);
	void AttackTarget();
};
