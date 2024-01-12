// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pills/BasePills.h"
#include "PainkillerPills.generated.h"

/**
 * 
 */
UCLASS()
class PSYCHO_API UPainkillerPills : public UBasePills
{
	GENERATED_BODY()
public:
	void UsePill() override;
};
