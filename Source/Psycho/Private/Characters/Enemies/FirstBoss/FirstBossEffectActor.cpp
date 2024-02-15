// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/FirstBoss/FirstBossEffectActor.h"

#include "Components/PoseableMeshComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AFirstBossEffectActor::AFirstBossEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	PoseableMeshComponent = CreateDefaultSubobject<UPoseableMeshComponent>("PoseableMeshComponent");
	SetRootComponent(PoseableMeshComponent);

}

void AFirstBossEffectActor::Create(USkeletalMeshComponent* NewSkeletalMeshComponent,USkeletalMesh* NewSkeletalMesh)
{
	if(NewSkeletalMeshComponent && NewSkeletalMesh && NewMaterial && GetWorld())
	{
		PoseableMeshComponent->SetSkeletalMesh(NewSkeletalMesh);
		PoseableMeshComponent->SetWorldLocation(GetActorLocation());
		PoseableMeshComponent->SetWorldRotation(GetActorRotation());
		for(int32 i=0;i<NewSkeletalMesh->Materials.Num();i++)
		{
			PoseableMeshComponent->SetMaterial(i,NewMaterial);	
		}
		PoseableMeshComponent->CopyPoseFromSkeletalComponent(NewSkeletalMeshComponent);
		GetWorld()->GetTimerManager().SetTimer(LiveTimerHandle,this,&AFirstBossEffectActor::EndLive,LiveTime);
	}
}

void AFirstBossEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AFirstBossEffectActor::EndLive()
{
	
	GetWorld()->GetTimerManager().ClearTimer(LiveTimerHandle);
	Destroy();
}


