// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CoreTypes.h"
#include "InputActionValue.h"
#include "Psycho/CoreTypes.h"
#include "AttackComponent.generated.h"

struct FInputActionValue;
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
	virtual void StartComboAttack(EComboInput Input);
	//конец комбинации атак
	void EndAttackCombo();
	
	void SetNextAttack(bool CanAttack){CanAttackNext=CanAttack;}
	void SetTimeAttack(bool CanAttack){CantAttackInTime=CanAttack;}
	
	//Перекат
	void SideDodge();
	//Ставим новое комбо в AttackComponent
	void SetCombo();
	//новое направление атаки
	void SetAttackDirection(const FVector2D& NewVector){AttackDirection=NewVector;}
	//новый форвард вектор относительно камеры
	void SetForwardDirection(const FVector& NewVector){ForwardDirection=NewVector;}
	//	новый правый вектор относительно камеры
	void SetRightDirection(const FVector& NewVector){RightDirection=NewVector;}
	//новая скорость атаки
	void MultiplyAttackSpeed(const float& Multiplier);
	//восстановление скорости атаки
	void ResetAttackSpeedToDefault();
	// новый множитель урона
	void MultiplyAttackDamage(const float& Multiplier){AttackDamage*=Multiplier;}
	void CommonDodge();
	//восстановление множителя урона
	void ResetAttackDamage(){AttackDamage=1.f;}
	//нанесение урона
	void Damage();
	// получить текущий номер атаки в комбинации
	int32 GetAttackIndex() const {return AttackIndex;}
	float GetTimeToEndCurrentAnimNotage() const {return TimeToEndCurrentAnimMontage;}
	
	//Номер текущего комбо
	int32 CurrentComboAttack = 0;
	

	bool GetIsDodge() const {return IsDodge;}
	
	int32 GetCurrentAttackDirection() const {return CurrentAttackDirection;}
	float GetCurrentAttackRepulsion() const {return CurrentAttackRepulsion;}
protected:
	virtual void BeginPlay() override;
	//массив комбо
	TArray<FCombination> Combos;

	//Угол между векторами
	static float GetAngle(const FVector& RightVector, const FVector& AnotherVector);

	//скорость поворота
	UPROPERTY(EditAnywhere,Category="Attack")
	float RotationSpeed = 60.0f;

	UPROPERTY(EditAnywhere,Category="Attack")
	float LengthOfDodge = 400.0f;
	
	//радиус сферы урона
	UPROPERTY(EditAnywhere,Category="Attack")
	float SphereDamageRadius=30.0f;
	//скорость атаки
	UPROPERTY(EditAnywhere,Category="Attack", meta = (ClampMin = "1.0"))
	float AttackSpeed = 1.f;
	UPROPERTY(EditAnywhere,Category="Attack", meta = (ClampMin = "1.0"))
	float AttackDamage = 1.f;

	UPROPERTY()
	UAnimMontage* CurrentAttackMontage;
	float TimeToEndCurrentAnimMontage=0.01f;

	//получаем владельца AttackComponent
	ABaseCharacter* GetCharacter() const;
	// получаем текущее оружие персонажа
	UWeaponComponent* GetWeaponComponent() const;
	//Номер текущей атаки в комбо
	int32 AttackIndex = 0;
	//Может ли атаковать продвинутым комбо
	bool CanAttackNext = false;
	//Попадает ли в тайминг обычной атаки
	bool CantAttackInTime = true;
	//Легкая Атака была уже использована
	bool IsLightAttackUse = false;
	FTimerHandle TimerEndAnimMontage;
	//Использование текущей атаки
	void ActiveAttack(FCombination& Attack);
	//Цель для атаки
	void AttackTarget() const;
	//Направление атаки при нанесение урона
	int32 CurrentAttackDirection=0;
	//Отталкивание данной атаки
	float CurrentAttackRepulsion=0.0f;

	void ChooseNewCurrentTheNearestDamagedCharacter(ABaseCharacter*& DamagedCharacter, const ABaseCharacter* ThisCharacter);
	
	FVector2D AttackDirection=FVector2d(0.0f,0.0f);
	FVector ForwardDirection;
	FVector RightDirection;
	//текущий тип атаки
	EComboInput CurrentComboInput= None;
	//Вычисление угла поворота атаки персонажа между ударами
	float RotationAngle(const ABaseCharacter* BaseCharacter) const;

	static FRotator CheckRotationWithAttack(const ABaseCharacter* DamagedActor, const ABaseCharacter* ThisCharacter,FRotator& Rotation);
	
	UPROPERTY()
	TArray<ABaseCharacter*> DamagedCharacters;
	UPROPERTY()
	ABaseCharacter* CurrentTheNearestDamagedCharacter;

	FTimerHandle DodgeTimer;
	bool IsDodge=false;
	void EndDodge();
	void EndSprintDodge();

	FInputActionValue Value;
	
	template<typename T> static int32 CompareSign(T, T);

	static int32 CheckAngle(const float& Angle);

	void IdealDodgeCheck(ABaseCharacter*& ThisCharacter) const;
	float CheckDodgeRadius=100.0f;
};

template <typename T>
int32 UAttackComponent::CompareSign(T First, T Second)
{
	return (First > Second) ? 1 : ((First < Second) ? -1 : 0);
}
