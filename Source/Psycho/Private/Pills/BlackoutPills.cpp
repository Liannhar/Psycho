// Fill out your copyright notice in the Description page of Project Settings.


#include "Pills/BlackoutPills.h"
#include "Characters/Player/PlayerCharacter.h"
#include "Characters/Components/AttackComponent.h"
#include "Characters/Components/PillsComponent.h"
#include "Enemies/BaseEnemy.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetArrayLibrary.h"

void UBlackoutPills::UsePill()
{
    if(GEngine)
        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, FString::Printf(TEXT("Blackout pill was taken")));

    APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

    if (!Player) return;

    FVector Start = Player->GetActorLocation();
	FVector End = Start;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(Player);
	TArray<FHitResult> HitResults;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));

	bool Hit = UKismetSystemLibrary::SphereTraceMultiForObjects(GetWorld(), Start, End, DeactivateRadius, ObjectTypesArray, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResults, true);

    if (Hit)
    {
        int32 MaxDeactivatedEnemies = FMath::RoundHalfFromZero((float)HitResults.Num() * (float)(DeactivatePercent) / 100.f);
        for (int32 i = 0; i < MaxDeactivatedEnemies; i++)
        {
            int32 Index = FMath::RandRange(0, HitResults.Num() - 1);
            ABaseEnemy* EnemyCharacter = Cast<ABaseEnemy>(HitResults[Index].GetActor());
            if (EnemyCharacter)
            {
                EnemyCharacter->Deactivate();
                DeactivatedEnemies.Add(EnemyCharacter);
                HitResults.RemoveAtSwap(Index);
            }
        }
    }

    GetWorld()->GetTimerManager().SetTimer(TimerPillEffect,this,&UBlackoutPills::StopBlurring,BlurringTime,false);
    Player->GetPillsComponent()->OnBlurringStart.Broadcast(BlurringStrength);
}


void UBlackoutPills::StopBlurring()
{
    for (ABaseEnemy* Enemy: DeactivatedEnemies)
    {
        Enemy->Reactivate();
    }

    if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
    {
        Player->GetPillsComponent()->OnBlurringEnd.Broadcast();
        Player->GetAttackComponent()->MultiplyAttackDamage(AttackDamageMultiplier);
        GetWorld()->GetTimerManager().ClearTimer(TimerPillEffect);
        GetWorld()->GetTimerManager().SetTimer(TimerPillEffect,this,&UBlackoutPills::StopDamageDecrease,DamageDecreaseTime,false);
    }
}

void UBlackoutPills::StopDamageDecrease()
{
    if (APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))
    {
        Player->GetAttackComponent()->ResetAttackDamage();
        GetWorld()->GetTimerManager().ClearTimer(TimerPillEffect);
    }
}
