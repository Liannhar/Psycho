// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/IdealDodgeAnimNotifyState.h"

#include "ComponentsCoreTypes.h"

void UIdealDodgeAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
	float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if(const auto BaseEnemy = GetBaseEnemy(MeshComp))
	{
		UE_LOG(LogTemp,Display,TEXT("AAAA1"));
		BaseEnemy->SetIdealDodge(true);
	}
}

void UIdealDodgeAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if(const auto BaseEnemy = GetBaseEnemy(MeshComp))
	{
		UE_LOG(LogTemp,Display,TEXT("BBBB1"));
		BaseEnemy->SetIdealDodge(false);
	}
}
