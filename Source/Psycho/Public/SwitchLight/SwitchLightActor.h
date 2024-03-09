// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwitchLightActor.generated.h"

class UNiagaraComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSwitchLight, ASwitchLightActor*, SwitchLightActor);

class UBoxComponent;

UCLASS()
class PSYCHO_API ASwitchLightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASwitchLightActor();

	bool GetNeedUse() const {return NeedUse;}
	void SetNeedUse(const bool& NewNeedUse){NeedUse=NewNeedUse;}

	FOnSwitchLight OnSwitchLight;

	UFUNCTION(BlueprintCallable)
	void SwitchLight(bool SwitchBool);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,Category="SmokeNiagara")
	UNiagaraComponent* InteractLight;
	
	UPROPERTY(EditAnywhere,Category="Components")
	UBoxComponent* CollisionComponent;
	UPROPERTY(EditAnywhere,Category="Components")
	UStaticMeshComponent* StaticMesh;
	UPROPERTY(EditAnywhere,Category="Components")
	USceneComponent* SceneComponent;

	UPROPERTY(BlueprintReadOnly)
	bool NeedUse=false;
	
};
