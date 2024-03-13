// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/SecondBoss/TentaculiActor.h"

#include "TentaculiDamage.h"
#include "Player/PlayerCharacter.h"

// Sets default values
ATentaculiActor::ATentaculiActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("Tentaculi");
	NiagaraComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATentaculiActor::BeginPlay()
{
	Super::BeginPlay();
	CurrentLocation=GetActorLocation();
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer,this,&ATentaculiActor::SpawnSphers,0.3f,true);
	}
	//NiagaraComponent->OnComponentBeginOverlap.AddDynamic(this,&ATentaculiActor::OverlapActor);
}


void ATentaculiActor::SpawnSphers()
{
	const auto Direction = Player->GetActorLocation()-CurrentLocation;
	const auto NormDirection = Direction.GetSafeNormal();
	CurrentLocation+=NormDirection*150.0f;

	/*if(GetWorld())
	{
		const auto TentaculiDamage = GetWorld()->SpawnActor<ATentaculiDamage>(CurrentLocation,GetActorRotation());
		TentaculiDamageActors.Add(TentaculiDamage);
	}*/
	UE_LOG(LogTemp,Display,TEXT("X %f Y %f Z %f "),NormDirection.X,NormDirection.Y,NormDirection.Z);
	NiagaraComponent->SetNiagaraVariableVec3("User.VelocityTentaculi",Direction/1.5f);
}

void ATentaculiActor::OverlapActor(AActor* InOwner)
{
	
}

