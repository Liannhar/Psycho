// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/SpawnDecalNotify.h"

#include "BaseCharacter.h"
#include "Components/DecalComponent.h"
#include "Engine/DecalActor.h"

void USpawnDecalNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	const auto Actor = MeshComp->GetOwner();
	if(!Actor) return;
	
	if(GetWorld() && DecalMaterial)
	{
		if(ADecalActor* NewDecalActor = GetWorld()->SpawnActor<ADecalActor>(ADecalActor::StaticClass(), Actor->GetActorLocation(), FRotator(0.0f, 0.0f, 0.0f)))
		{
			NewDecalActor->SetDecalMaterial(DecalMaterial);
			NewDecalActor->SetActorLocation(FVector(NewDecalActor->GetActorLocation().X+Actor->GetActorForwardVector().X*ChangeLocationPositionForwardDecal,NewDecalActor->GetActorLocation().Y+Actor->GetActorForwardVector().Y*ChangeLocationPositionForwardDecal,NewDecalActor->GetActorLocation().Z-100.0f)); 
			NewDecalActor->GetDecal()->DecalSize = DecalSize;
		}
	}
}
