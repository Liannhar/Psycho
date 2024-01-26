// Fill out your copyright notice in the Description page of Project Settings.


#include "Pills/FuryPills.h"
#include "Characters/Player/PlayerCharacter.h"
#include "Characters/Components/AttackComponent.h"
#include "Characters/Components/HealthComponent.h"
#include "Characters/Components/PillsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void UFuryPills::UsePill()
{
    if(GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Fury pill was taken")));

    APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
    
    if (!Player) return;

    Player->GetCharacterMovement()->MaxWalkSpeed *= SpeedMultiplier;
    Player->GetAttackComponent()->MultiplyAttackSpeed(AttackSpeedMultiplier);
    GetWorld()->GetTimerManager().SetTimer(TimerPillEffect,this,&UFuryPills::StopTakeDamage,TakeDamageTime,false);
    GetWorld()->GetTimerManager().SetTimer(TimerTakeDamageTick,this,&UFuryPills::TakeDamage,TakeDamageTickTime,true);
    Player->GetPillsComponent()->SetFuryEffectsTimer(TimerPillEffect);
}


void UFuryPills::TakeDamage()
{
    if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
    {
        float Damage = Player->GetHealthComponent()->GetMaxHP() * TakeDamagePercent / 100.f;
        UGameplayStatics::ApplyDamage(Player, Damage, Player->GetController(), Player, UDamageType::StaticClass());
    }
}


void UFuryPills::StopTakeDamage()
{
    if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
    {
        GetWorld()->GetTimerManager().ClearTimer(TimerPillEffect);
        GetWorld()->GetTimerManager().ClearTimer(TimerTakeDamageTick);
        Player->GetCharacterMovement()->MaxWalkSpeed /= SpeedMultiplier;
        Player->GetAttackComponent()->ResetAttackSpeedToDefault();
        Player->GetHealthComponent()->ResetTakeDamageMultiplier();
    }
}
