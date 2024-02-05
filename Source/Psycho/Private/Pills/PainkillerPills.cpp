// Fill out your copyright notice in the Description page of Project Settings.


#include "Pills/PainkillerPills.h"
#include "Characters/Player/PlayerCharacter.h"
#include "Characters/Components/AttackComponent.h"
#include "Characters/Components/HealthComponent.h"
#include "Characters/Components/PillsComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

void UPainkillerPills::UsePill()
{
    Super::UsePill();

    if(GEngine)
     GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Painkiller pill was taken")));
  
    if (!Player) return;

    // Setting invulnerability timer
    Player->GetHealthComponent()->isInvulnerable = true;
    Player->GetCharacterMovement()->MaxWalkSpeed *= SpeedMultiplier;
    Player->GetAttackComponent()->MultiplyAttackSpeed(AttackSpeedMultiplier);
    GetWorld()->GetTimerManager().SetTimer(PillEffectsTimer,this,&UPainkillerPills::EndInvulnerability,InvulnerabilityTime,false);
    Player->GetPillsComponent()->SetPillEffectsTimer(PillEffectsTimer);
}


void UPainkillerPills::EndInvulnerability()
{
    if (Player)
    {
        Player->GetHealthComponent()->isInvulnerable = false;
        Player->GetHealthComponent()->SetTakeDamageMultiplier(TakeDamageMultiplier);
        Player->GetCharacterMovement()->MaxWalkSpeed /= SpeedMultiplier;
        Player->GetAttackComponent()->ResetAttackSpeedToDefault();
        GetWorld()->GetTimerManager().ClearTimer(PillEffectsTimer);
        GetWorld()->GetTimerManager().SetTimer(PillAfterEffectsTimer,this,&UPainkillerPills::EndAddiction,AddicitonTime,false);
        Player->GetPillsComponent()->SetPillAfterEffectsTimer(PillAfterEffectsTimer);
    }
}


void UPainkillerPills::EndAddiction()
{
    if (Player)
    {
        Player->GetHealthComponent()->ResetTakeDamageMultiplier();
        GetWorld()->GetTimerManager().ClearTimer(PillAfterEffectsTimer);
    }
}
