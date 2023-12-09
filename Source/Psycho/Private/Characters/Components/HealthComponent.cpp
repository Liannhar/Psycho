// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/HealthComponent.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (MaxHP > 0) CalculatePercentHP();
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


float UHealthComponent::CalculatePercentHP()
{
	int Precission = 2;
	int X = FMath::Pow(10, Precission);
	return PercentHP = FMath::RoundHalfFromZero(X * (CurrentHP / MaxHP)) / X;
}

float UHealthComponent::GetMaxHP()
{
	return MaxHP;
}

float UHealthComponent::GetCurrentHP()
{
	return CurrentHP;
}

float UHealthComponent::GetPercentHP()
{
	return PercentHP;
}


void UHealthComponent::ApplyDamage(float Damage)
{
	CurrentHP = FMath::Clamp(CurrentHP - Damage, 0, MaxHP);
	CalculatePercentHP();

	if (CurrentHP == 0)
	{ 
		OnDied();
	}

	if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(
		TEXT("%s was attacked! %s has %f HP"), *(GetOwner()->GetName()), *(GetOwner()->GetName()), CurrentHP));
}

void UHealthComponent::RestoreHP(float RestoreAmount)
{
	CurrentHP = FMath::Clamp(CurrentHP + RestoreAmount, 0, MaxHP);
	CalculatePercentHP();
}

void UHealthComponent::OnDied()
{
	if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("%s died!"), *(GetOwner()->GetName())));
}
