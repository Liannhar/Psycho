// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BasePillActor.generated.h"

UCLASS()
class PSYCHO_API ABasePillActor : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Mesh, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = Pill, meta = (AllowPrivateAccess = "true"))
	class UPillsDataStructure* PillData;

	void PostEditChangeProperty(struct FPropertyChangedEvent& e) override;
public:	
	// Sets default values for this actor's properties
	ABasePillActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	virtual void OnInteract(class APlayerCharacter* Player);
};
