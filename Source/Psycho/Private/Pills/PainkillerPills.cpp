// Fill out your copyright notice in the Description page of Project Settings.


#include "Pills/PainkillerPills.h"


void UPainkillerPills::UsePill()
{
    if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Painkiller pill was taken")));
}
