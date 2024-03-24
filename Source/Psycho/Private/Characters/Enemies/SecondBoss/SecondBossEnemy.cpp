// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/SecondBoss/SecondBossEnemy.h"

#include "FirstStageSecondBossComponent.h"
#include "HealthComponent.h"
#include "NiagaraComponent.h"
#include "SecondBossBaseEnemyVersion.h"
#include "SecondBossEnemyAIController.h"
#include "SecondStageSecondBossComponent.h"
#include "TentaculiActor.h"
#include "ThirdStageSecondBossComponent.h"
#include "Player/PlayerCharacter.h"

ASecondBossEnemy::ASecondBossEnemy()
{
	FirstStageSecondBossComponent=CreateDefaultSubobject<UFirstStageSecondBossComponent>("FirstStage");
	SecondStageSecondBossComponent=CreateDefaultSubobject<USecondStageSecondBossComponent>("SecondStage");
	ThirdStageSecondBossComponent=CreateDefaultSubobject<UThirdStageSecondBossComponent>("ThirdStage");
	SmokeNiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("FirstSmokeNiagara");
	SmokeNiagaraComponent->SetupAttachment(RootComponent);
}

void ASecondBossEnemy::BeginPlay()
{
	Super::BeginPlay();
	SecondBossEnemyAIController=Cast<ASecondBossEnemyAIController>(OwnController);
}

void ASecondBossEnemy::StartBoss()
{
	//TODO for tests
	NextStage=ThirdStage;
	ChangeStage(NextStage);
}



void ASecondBossEnemy::ChangeStage(const ESecondBossStages& NewStage)
{
	switch (NewStage)
	{
	case FirstStage:
		{
			ChangeBehaviorTreeAsset(FirstStageSecondBossComponent->GetBehaviorTree());
			FirstStageSecondBossComponent->FirstStageAction();
			NextStage=SecondStage;
			break;
		}
	case SecondStage:
		{
			ChangeBehaviorTreeAsset(SecondStageSecondBossComponent->GetBehaviorTree());
			SecondStageSecondBossComponent->SecondStageStartAction();
			NextStage=ThirdStage;
			break;
		}
	case ThirdStage:
		{
			ChangeBehaviorTreeAsset(ThirdStageSecondBossComponent->GetBehaviorTree());
			ThirdStageSecondBossComponent->ThirdStageStartAction();
			NextStage=FirstStage;
			break;
		}
	}
}





void ASecondBossEnemy::ChangeInvulnerable(const bool&& NewBool) const
{
	HealthComponent->bIsInvulnerable=NewBool;
}

void ASecondBossEnemy::EndStage()
{
	ChangeStage(NextStage);
}

void ASecondBossEnemy::ScreamAttack()
{
	bScreamAttack=true;
	const float ScreamTime = PlayAnimMontage(ScreamMontage);
	if(GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(EndScreamTimer,this,&ASecondBossEnemy::EndScreamAttack,ScreamTime);
	}
	ScreamLogic();
}

void ASecondBossEnemy::ScreamLogic()
{
	FVector Start = GetActorLocation();
	FVector End = SecondBossEnemyAIController->GetPlayerCharacter()->GetActorLocation()+FVector(10.f,10.f,0.0f);
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	FHitResult HitResult;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesArray;
	ObjectTypesArray.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn));

	if (!UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), Start, End, ScreamRadius, ObjectTypesArray, false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true)) return;
	
	if(const auto&& Player = Cast<APlayerCharacter>(HitResult.GetActor()))
	{
		Player->ScreamReaction(this);
	}
}

void ASecondBossEnemy::EndScreamAttack()
{
	bScreamAttack=false;
	if(GetWorld())
	{
		//GetWorld()->GetTimerManager().ClearTimer(ScreamTimer);
		GetWorld()->GetTimerManager().ClearTimer(EndScreamTimer);
	}
}


void ASecondBossEnemy::CircleAction(const int32& CountEnemies)
{
	if(GetWorld())
	{
		PlayerLocation = SecondBossEnemyAIController->GetPlayerCharacter()->GetActorLocation();
		/*BlockCylinder = GetWorld()->SpawnActor<ABlockingVolume>(ABlockingVolume::StaticClass(),PlayerLocation,GetActorRotation());

		const auto Angle = 360.f/CountEnemies;
		BlockCylinder->Brush->NumSharedSides=CountEnemies;*/
		LocationsAroundPlayer = FindLocationsAroundPlayer();
		SpawnEnemies(CountEnemies);
	}
}

void ASecondBossEnemy::SpawnEnemies(const int32& CountEnemies)
{
	if(GetWorld())
	{
		PlayerLocation = SecondBossEnemyAIController->GetPlayerCharacter()->GetActorLocation();
		const auto Player = SecondBossEnemyAIController->GetPlayerCharacter();
		MaxCountEnemies=CountEnemies-1;
		SetActorLocation(PlayerLocation+SpawnRadiusAroundPlayer*Player->GetActorForwardVector().RotateAngleAxis(0.0f,FVector(0,0,1.f)));
		
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer,this,&ASecondBossEnemy::SpawnOneEnemy,0.2f,true);
	}
}


void ASecondBossEnemy::SpawnOneEnemy()
{
	if(!GetWorld()) return;
	
	if(CurrentEnemyCount==MaxCountEnemies)
	{
		CurrentEnemyCount=0;
		MaxCountEnemies=0;
		GetWorld()->GetTimerManager().ClearTimer(SpawnTimer);
	}

	if(CurrentEnemyCount>=LocationsAroundPlayer.Num())
	{
		return;
	}
	
	if(const auto Enemy = GetWorld()->SpawnActor<ASecondBossBaseEnemyVersion>(SecondBossSubClass,LocationsAroundPlayer[CurrentEnemyCount],GetActorRotation()))
	{
		SpawnedEnemies.Add(Enemy);
		CurrentEnemyCount++;
		Enemy->GetHealthComponent()->OnDeath.AddUObject(this,&ASecondBossEnemy::DeleteEnemy);	
	}
}

void ASecondBossEnemy::DeleteEnemy(ABaseCharacter* BaseCharacter)
{
	if(const auto Enemy = Cast<ASecondBossBaseEnemyVersion>(BaseCharacter))
	{
		SpawnedEnemies.Remove(Enemy);
	}
	
}

TArray<FVector> ASecondBossEnemy::FindLocationsAroundPlayer() const
{
	if(PlayerLocation.IsZero()) return TArray<FVector>();
	auto Locations = TArray<FVector>();

	const float AngleChange = 360.0f/MaxCountEnemies;
	float Angle=AngleChange;

	const auto PlayerForwardVector = SecondBossEnemyAIController->GetPlayerCharacter()->GetActorForwardVector();

	for(int32 i=0;i<MaxCountEnemies;i++)
	{
		const auto NewLocation=PlayerLocation+SpawnRadiusAroundPlayer*PlayerForwardVector.RotateAngleAxis(Angle,FVector(0,0,1.f));
		Locations.Add(NewLocation);
		Angle=FMath::Clamp(Angle+AngleChange,0.0f,360.f);
	}
	return Locations;
}

void ASecondBossEnemy::ActivateTentaculis()
{
	if(ActiveTimerHandleTentaciuli.IsValid()) return;
	

	for(const auto& Tentaculi:Tentaculis)
	{
		Tentaculi->Activate();
	}

	if(GetWorld()) GetWorld()->GetTimerManager().SetTimer(ActiveTimerHandleTentaciuli,this,&ASecondBossEnemy::DeactivateTentaculis,TentaculiActiveTime);

}

void ASecondBossEnemy::DeactivateTentaculis()
{
	if(GetWorld() ) GetWorld()->GetTimerManager().ClearTimer(ActiveTimerHandleTentaciuli);
	
	for(const auto& Tentaculi:Tentaculis)
	{
		Tentaculi->Deactivate();
	}
}


