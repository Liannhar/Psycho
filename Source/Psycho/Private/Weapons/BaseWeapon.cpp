// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"
#include "Components/CapsuleComponent.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>("Capsule component");
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal Mesh");
	CollisionComponent->InitCapsuleSize(15,32);
	CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetRootComponent(SkeletalMeshComponent);
	CollisionComponent->SetupAttachment(RootComponent);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	//нанести урон и проверить, что это enemy
}

void ABaseWeapon::StartAttack()
{
	IsAttacking=true;
	CollisionComponent->SetCollisionResponseToChannel(ECC_Pawn,ECR_Overlap);
}

void ABaseWeapon::EndAttack()
{
	IsAttacking=false;
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
}

