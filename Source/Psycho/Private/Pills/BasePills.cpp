// Fill out your copyright notice in the Description page of Project Settings.


#include "Pills/BasePills.h"
#include "Characters/Player/PlayerCharacter.h"
#include "Structures/PillsDataStructure.h"
#include "Kismet/GameplayStatics.h"


void UBasePills::Init(UPillsDataStructure* Data)
{
    if (!Data && !Data->GetIcon()) return;

    Icon = Data->GetIcon();
}

void UBasePills::UsePill()
{
    Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}
