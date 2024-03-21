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
	
	CurrentLocation=FVector(0.0f,0.0f,TentaculiParameters.Height);
	NiagaraComponent->SetNiagaraVariableVec3("User.VelocityTentaculi",CurrentLocation);
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(AttackTimer,this,&ATentaculiActor::NiagaraChangePosition,1.f,true,StartWaitTime);
	}

	Deactivate();
}

void ATentaculiActor::NiagaraChangePosition()
{
	const auto NewTargetLocation = Player->GetActorLocation();
	const auto NewActorLocation=GetActorLocation();
	const auto DistanceBetweenPlayerTentaculi =  NewTargetLocation-NewActorLocation;

	if(!CheckIsPlayerNearTentaculi(DistanceBetweenPlayerTentaculi))
	{
		ReturnInStartPosition(WaitTimeAfterCheckRadius);
		return;
	}

	const auto Direction =DistanceBetweenPlayerTentaculi/3.f;
	const auto NormDirection = Direction.GetSafeNormal();
	
	const float AngleDirectionX = NewActorLocation.X>NewTargetLocation.X?1.f:-1.f;
	const float AngleDirectionY = NewActorLocation.Y>NewTargetLocation.Y?-1.f:1.f;
	
	const float ClampedX = CurrentLocation.X+AngleDirectionX*TentaculiParameters.Speed*NormDirection.X;
	const float ClampedY = CurrentLocation.Y+AngleDirectionY*TentaculiParameters.Speed*NormDirection.Y;
	const float ClampedZ = CurrentLocation.Z+TentaculiParameters.Speed*NormDirection.Z+HeightAttackZ;

	CurrentLocation = FVector(ClampedX, ClampedY, ClampedZ);
	
	NiagaraComponent->SetNiagaraVariableVec3("User.VelocityTentaculi",Direction);
}

bool ATentaculiActor::CheckIsPlayerNearTentaculi(const FVector& Distance)
{
	return Distance.Size() <= TentaculiParameters.Radius;
}

void ATentaculiActor::NiagaraChangeBackPosition()
{
	NiagaraComponent->SetNiagaraVariableVec3("User.VelocityTentaculi",CurrentLocation);
}

void ATentaculiActor::OnComponentBeginOverlap()
{
	if(GetWorld()  && !TimerHandle.IsValid())
	{
		const auto DamageType = NewObject<UDamageType>() ;
		Player->GetHealthComponent()->ApplyDamage(Player,Damage,DamageType,GetController(),this);
		ReturnInStartPosition(WaitTimeAfterAttack);
	}
}

void ATentaculiActor::ReturnInStartPosition(float WaitNextAttackAttemptTime)
{
	CurrentLocation= FVector(0.0f,0.0f,TentaculiParameters.Height);
	GetWorld()->GetTimerManager().ClearTimer(AttackTimer);
	GetWorld()->GetTimerManager().SetTimer(AttackTimer,this,&ATentaculiActor::NiagaraChangeBackPosition,0.1f,true);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle,this,&ATentaculiActor::EndWait,WaitNextAttackAttemptTime);
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


void ATentaculiActor::Activate() const
{
	NiagaraComponent->SetVisibility(true);
	NiagaraComponent->Activate();
}

void ATentaculiActor::Deactivate() const
{
	NiagaraComponent->Deactivate();
	NiagaraComponent->SetVisibility(false);
}
