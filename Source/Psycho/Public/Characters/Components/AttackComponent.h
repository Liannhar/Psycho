// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoreTypes.h"
#include "Psycho/CoreTypes.h"
#include "AttackComponent.generated.h"

class ABaseEnemy;
class UWeaponComponent;
class ABaseCharacter;
struct FCombination;
class ABaseWeapon;


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PSYCHO_API UAttackComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAttackComponent();
	//начало комбинации атак
	void StartAttack(EComboInput Input);
	//конец комбинации атак
	void EndAttack();
	
	void SetNextAttack(bool CanAttack){CanAttackNext=CanAttack;}
	void SetTimeAttack(bool CanAttack){CantAttackInTime=CanAttack;}

	//Ставим новое комбо в AttackComponent
	void SetCombo();
	//новое направление атаки
	void SetAttackDirection(const FVector2D& NewVector){AttackDirection=NewVector;}
	//новый форвард вектор относительно камеры
	void SetForwardDirection(const FVector& NewVector){ForwardDirection=NewVector;}
	//	новый правый вектор относительно камеры
	void SetRightDirection(const FVector& NewVector){RightDirection=NewVector;}
	//нанесение урона
	void Damage();
	// получить текущий номер атаки в комбинации
	int32 GetAttackIndex() const {return AttackIndex;}
	
	
protected:
	virtual void BeginPlay() override;
	//массив комбо
	TArray<FCombination> Combos;
	//скорость поворота
	UPROPERTY(EditAnywhere,Category="Attack")
	float RotationSpeed = 60.0f;
	//длина попадания атаки для урона
	UPROPERTY(EditAnywhere,Category="Attack")
	float LengthLineAttack=100.0f;
	//радиус сферы урона
	UPROPERTY(EditAnywhere,Category="Attack")
	float SphereDamageRadius=30.0f;

	
private:
	//получаем владельца AttackComponent
	ABaseCharacter* GetCharacter() const;
	// получаем текущее оружие персонажа
	UWeaponComponent* GetWeaponComponent() const;
	//Номер текущей атаки в комбо
	int32 AttackIndex = 0;
	//Номер текущего комбо
	int32 CurrentComboAttack = 0;
	//Может ли атаковать продвинутым комбо
	bool CanAttackNext = false;
	//Попадает ли в тайминг обычной атаки
	bool CantAttackInTime = true;
	FTimerHandle TimerEndAnimMontage;
	//Использование текущей атаки
	void ActiveAttack(FCombination Attack);
	//Цель для атаки
	void AttackTarget() const;

	void ChooseNewCurrentTheNearestDamagedCharacter(ABaseCharacter* DamagedCharacter, const ABaseCharacter* ThisCharacter);
	
	FVector2D AttackDirection=FVector2d(0.0f,0.0f);
	FVector ForwardDirection;
	FVector RightDirection;
	//текущий тип атаки
	EComboInput CurrentComboInput= None;
	//Вычисление угла поворота атаки персонажа между ударами
	float RotationAngle(const ABaseCharacter* BaseCharacter) const;

	static FRotator CheckRotationWithAttack(ABaseCharacter* DamagedActor,ABaseCharacter* ThisCharacter,FRotator Rotation);
	
	UPROPERTY()
	TArray<ABaseCharacter*> DamagedCharacters;
	UPROPERTY()
	ABaseCharacter* CurrentTheNearestDamagedCharacter;
};
