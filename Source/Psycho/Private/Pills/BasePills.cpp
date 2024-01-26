// Fill out your copyright notice in the Description page of Project Settings.


#include "Pills/BasePills.h"
#include "Structures/PillsDataStructure.h"


void UBasePills::Init(UPillsDataStructure* Data)
{
    if (!Data && !Data->GetIcon()) return;

    Icon = Data->GetIcon();
}

void UBasePills::UsePill()
{
    if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("%s pill was taken"), *GetName()));
}
