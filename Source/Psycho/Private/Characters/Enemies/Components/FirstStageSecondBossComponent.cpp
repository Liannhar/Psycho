// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/Components/FirstStageSecondBossComponent.h"

#include "SecondBossEnemy.h"
#include "Components/LightComponent.h"
#include "Engine/PointLight.h"
#include "SwitchLight/SwitchLightActor.h"

UFirstStageSecondBossComponent::UFirstStageSecondBossComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFirstStageSecondBossComponent::BeginPlay()
{
	Super::BeginPlay();
	SecondBoss = Cast<ASecondBossEnemy>(GetOwner());
}

void UFirstStageSecondBossComponent::FirstStageAction()
{
	if(SecondBoss)
	{
		SecondBoss->ChangeInvulnerable(true);
		SecondBoss->ChangeNiagaraVisibility(true);	
	}
	ChangeIntensityAllLights(DimLight);
	EnableSwitchLightActors();
}

void UFirstStageSecondBossComponent::EnableSwitchLightActors()
{
	
	CurrentTurnedOnSwitchLightActors.Empty();
	
	HowManySwitchLightsActorsNeedEnable= HowManySwitchLightsActorsNeedEnable>SwitchLightsActors.Num()?SwitchLightsActors.Num():HowManySwitchLightsActorsNeedEnable;
	auto RandomSwitchLightActorIndex = FMath::RandRange(0, SwitchLightsActors.Num()-1);
	for (int32 i=0;i<HowManySwitchLightsActorsNeedEnable;i++)
	{
		RandomSwitchLightActorIndex+=FMath::RandRange(1, 2);
		if(RandomSwitchLightActorIndex>SwitchLightsActors.Num()-1)
		{
			RandomSwitchLightActorIndex=0;
		}
		if(!SwitchLightsActors[RandomSwitchLightActorIndex]->GetNeedUse())
		{
			SwitchLightsActors[RandomSwitchLightActorIndex]->SwitchLight(true);
			SwitchLightsActors[RandomSwitchLightActorIndex]->OnSwitchLight.AddDynamic(this,&UFirstStageSecondBossComponent::TurnOffSwitchLight);
			CurrentTurnedOnSwitchLightActors.Add(SwitchLightsActors[RandomSwitchLightActorIndex]);
			continue;
		}
		i--;
	}
}

void UFirstStageSecondBossComponent::ChangeIntensityAllLights(const float& NewIntensity)
{
	for(const auto& PointLight:PointsLightsOnLevel)
	{
		if(PointLight)
		{
			PointLight->GetLightComponent()->SetIntensity(NewIntensity);
		}
	}
}

void UFirstStageSecondBossComponent::TurnOffSwitchLight(ASwitchLightActor* SwitchLightActor)
{
	if(CurrentTurnedOnSwitchLightActors.Contains(SwitchLightActor))
	{
		CurrentTurnedOnSwitchLightActors.Remove(SwitchLightActor);
	}

	if(CurrentTurnedOnSwitchLightActors.Num()==0)
	{
		EndFirstStage();
	}
}

void UFirstStageSecondBossComponent::EndFirstStage()
{
	ChangeIntensityAllLights(BrightLight);
	SecondBoss->ChangeInvulnerable(false);
	SecondBoss->ChangeNiagaraVisibility(false);
	SecondBoss->EndStage();
}