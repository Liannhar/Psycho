#pragma once

#include "SecondBossCoreTypes.generated.h"

USTRUCT(BlueprintType)
struct FTentaculiParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,Category="Tentaculi")
	float Speed=40.f;
	UPROPERTY(EditAnywhere,Category="Tentaculi")
	float Height=40.f;
	UPROPERTY(EditAnywhere,Category="Tentaculi")
	float Radius=200.f;
};
	
