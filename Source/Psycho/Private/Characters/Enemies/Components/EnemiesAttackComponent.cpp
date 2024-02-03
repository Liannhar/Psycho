// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/Components/EnemiesAttackComponent.h"

void UEnemiesAttackComponent::StartComboAttack(EComboInput Input)
{
	DamagedCharacters.Empty();
	for (int32 i=CurrentComboAttack; i < Combos.Num();i++ )
	{
		if(AttackIndex<Combos[i].Attack.Num() && Combos[i].Attack[AttackIndex].TypeAttack==Input && (AttackIndex==0  || !CantAttackInTime|| CanAttackNext ))
		{
			
			CurrentComboInput=Combos[i].Attack[AttackIndex].TypeAttack;
			if(Combos[i].Attack[AttackIndex].PreviosAttackNeedTiming)
			{
				if( CanAttackNext )
				{
					CurrentComboAttack=i;
					ActiveAttack(Combos[i]);	
					break;	
				}
				continue;
			}

			CurrentComboAttack=i;
			ActiveAttack(Combos[i]);
			break;
		}
	}
}
