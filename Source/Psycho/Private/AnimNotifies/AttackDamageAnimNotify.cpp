// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimNotifies/AttackDamageAnimNotify.h"

#include "ComponentsCoreTypes.h"

class UAttackComponent;

//При вызове Notify вызываем функцию Damage владельца MeshComp
void UAttackDamageAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);
	if(const auto AttackComponent = GetAttackComponent(MeshComp))
	{
		AttackComponent->Damage();
	}
}

