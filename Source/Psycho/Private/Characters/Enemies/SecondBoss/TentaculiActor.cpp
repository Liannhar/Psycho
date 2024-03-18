// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/SecondBoss/TentaculiActor.h"

#include "HealthComponent.h"
#include "Player/PlayerCharacter.h"

ATentaculiActor::ATentaculiActor()
{
	PrimaryActorTick.bCanEverTick = false;
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("Tentaculi");
	NiagaraComponent->SetupAttachment(RootComponent);
}

void ATentaculiActor::BeginPlay()
{
	Super::BeginPlay();
	CurrentLocation=FVector(0.0f,0.0f,Height);
	NiagaraComponent->SetNiagaraVariableVec3("User.VelocityTentaculi",CurrentLocation);
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(AttackTimer,this,&ATentaculiActor::NiagaraChangePosition,1.f,true,StartWaitTime);
	}
}

void ATentaculiActor::NiagaraChangePosition()
{
	const auto NewTargetLocation = Player->GetActorLocation();
	const auto NewActorLocation=GetActorLocation();
	UE_LOG(LogTemp,Display,TEXT("NTL x %f y %f z %f"),NewTargetLocation.X,NewTargetLocation.Y,NewTargetLocation.Z);
	const auto Direction = (NewTargetLocation-NewActorLocation)/3.f;
	UE_LOG(LogTemp,Display,TEXT("D x %f y %f z %f"),Direction.X,Direction.Y,Direction.Z);
	const auto NormDirection = Direction.GetSafeNormal();
	UE_LOG(LogTemp,Display,TEXT("ND x %f y %f z %f"),NormDirection.X,NormDirection.Y,NormDirection.Z);

	
	const float AngleDirectionX = NewActorLocation.X>NewTargetLocation.X?1.f:-1.f;
	const float AngleDirectionY = NewActorLocation.Y>NewTargetLocation.Y?-1.f:1.f;
	//const float AngleDirectionZ = NewActorLocation.Z>NewTargetLocation.Z?-1.f:1.f;
	
	const float ClampedX = CurrentLocation.X+AngleDirectionX*Speed*NormDirection.X;
	const float ClampedY = CurrentLocation.Y+AngleDirectionY*Speed*NormDirection.Y;
	const float ClampedZ = CurrentLocation.Z+Speed*NormDirection.Z;

	CurrentLocation = FVector(ClampedX, ClampedY, ClampedZ);
	UE_LOG(LogTemp,Display,TEXT("CP x %f y %f z %f"),CurrentLocation.X,CurrentLocation.Y,CurrentLocation.Z);

	
	NiagaraComponent->SetNiagaraVariableVec3("User.VelocityTentaculi",Direction);
}


void ATentaculiActor::NiagaraChangeBackPosition()
{
	/*const auto NullVector = FVector(0.0f,0.0f,Height);
	const auto Direction =NullVector -CurrentLocation;
	const auto NormDirection = Direction.GetSafeNormal();
	const float ClampedX = FMath::Clamp(CurrentLocation.X+Speed*NormDirection.X, NullVector.X, CurrentLocation.X);
	const float ClampedY = FMath::Clamp(CurrentLocation.Y+Speed*NormDirection.Y, NullVector.Y, CurrentLocation.Y);
	const float ClampedZ = FMath::Clamp(CurrentLocation.Z+Speed*NormDirection.Z,CurrentLocation.Z, NullVector.Z);

	CurrentLocation = FVector(ClampedX, ClampedY, ClampedZ);*/
	NiagaraComponent->SetNiagaraVariableVec3("User.VelocityTentaculi",CurrentLocation);
}

void ATentaculiActor::OnComponentBeginOverlap()
{
	if(GetWorld()  && !TimerHandle.IsValid())
	{
		const auto DamageType = NewObject<UDamageType>() ;
		Player->GetHealthComponent()->ApplyDamage(Player,Damage,DamageType,GetController(),this);
		CurrentLocation= FVector(0.0f,0.0f,Height);
		GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ATentaculiActor::EndWait,WaitTime);
		GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
		GetWorld()->GetTimerManager().SetTimer(AttackTimer,this,&ATentaculiActor::NiagaraChangeBackPosition,0.1f,true);
		
	}
	
}

void ATentaculiActor::EndWait()
{
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
		GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
		GetWorld()->GetTimerManager().SetTimer(AttackTimer,this,&ATentaculiActor::NiagaraChangePosition,0.1f,true);
		
	}
}
