// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/SecondBoss/TentaculiDamage.h"

#include "AttackDamageType.h"
#include "HealthComponent.h"
#include "TentaculiActor.h"
#include "Components/SphereComponent.h"
#include "Player/PlayerCharacter.h"

ATentaculiDamage::ATentaculiDamage()
{
	PrimaryActorTick.bCanEverTick = false;
	Sphere = CreateDefaultSubobject<USphereComponent>("Collision");
	Sphere->SetupAttachment(RootComponent);
	Sphere->InitSphereRadius(30.0f);
	RootComponent=Sphere;
}

void ATentaculiDamage::BeginPlay()
{
	Super::BeginPlay();
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(DeleteTimer,this,&ATentaculiDamage::Delete,0.3f,true);
	}
}

void ATentaculiDamage::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if(const auto PlayerCharacter = Cast<APlayerCharacter>(OtherActor))
	{
		const auto DamageType = NewObject<UAttackDamageType>();
		PlayerCharacter->GetHealthComponent()->ApplyDamage(PlayerCharacter,Damage,DamageType,nullptr,this);
	}
}

void ATentaculiDamage::Delete()
{
	Destroy();
}

