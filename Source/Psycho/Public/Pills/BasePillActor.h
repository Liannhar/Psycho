// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePillActor.generated.h"

struct FPropertyChangedEvent;

UCLASS()
class PSYCHO_API ABasePillActor : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Pill, meta = (AllowPrivateAccess = "true"))
	class UPillsDataStructure* PillData;

public:	
	ABasePillActor();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void OnInteract(class APlayerCharacter* Player);

	virtual void PostEditChangeProperty(FPropertyChangedEvent& E) override;
};
