// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/FirstBossDeathAnimNotify.h"

#include "FirstBossEnemy.h"


void UFirstBossDeathAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	const auto Actor = MeshComp->GetOwner();
	if(!Actor) return ;
	const auto FirstBoss = Cast<AFirstBossEnemy>(Actor);
	if(!FirstBoss) return;

	FirstBoss->DeathConfigurations();
	
}
