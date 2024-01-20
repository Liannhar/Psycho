// Fill out your copyright notice in the Description page of Project Settings.


#include "BoolBTDecorator.h"

#include "BehaviorTree/BlackboardComponent.h"

UBoolBTDecorator::UBoolBTDecorator()
{
	NodeName="Bool decorator";
}

bool UBoolBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	if(Inverse) return !BlackBoard->GetValueAsBool(BoolKey.SelectedKeyName);

	return BlackBoard->GetValueAsBool(BoolKey.SelectedKeyName);
}
