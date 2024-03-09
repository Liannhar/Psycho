// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/IdealDodgeAnimNotifyState.h"

#include "ComponentsCoreTypes.h"

void UIdealDodgeAnimNotifyState::BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyBegin(BranchingPointPayload);
	
	if(const auto BaseEnemy = GetBaseEnemy(BranchingPointPayload.SkelMeshComponent))
	{
		BaseEnemy->SetIdealDodge(true);
	}
}

void UIdealDodgeAnimNotifyState::BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::BranchingPointNotifyEnd(BranchingPointPayload);
	if(const auto BaseEnemy = GetBaseEnemy(BranchingPointPayload.SkelMeshComponent))
	{
		BaseEnemy->SetIdealDodge(false);
	}
}
