// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Components/AttackComponent.h"

UAttackComponent::UAttackComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}


void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

