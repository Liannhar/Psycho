// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/Enemies/AI/Nodes/ChangeBoolBTTaskNode.h"

#include "BehaviorTree/BlackboardComponent.h"

UChangeBoolBTTaskNode::UChangeBoolBTTaskNode()
{
	NodeName="ChangeBool";
}

EBTNodeResult::Type UChangeBoolBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto BlackBoard = OwnerComp.GetBlackboardComponent();
	BlackBoard->SetValueAsBool(Key.SelectedKeyName,NewBool);
	return EBTNodeResult::Succeeded;
}
