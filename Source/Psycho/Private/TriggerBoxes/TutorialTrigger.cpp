// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerBoxes/TutorialTrigger.h"
#include "ActorComponents/TutorialWidgetComponent.h"

ATutorialTrigger::ATutorialTrigger()
{
    TutorialWidgetComponent = CreateDefaultSubobject<UTutorialWidgetComponent>(TEXT("Tutorial Widget Component"));
    TutorialWidgetComponent->TutorialClosed.AddUObject(this, &ATutorialTrigger::DestroyTrigger);
}

void ATutorialTrigger::End()
{

}

void ATutorialTrigger::BeginPlay()
{
    Super::BeginPlay();

    TutorialWidgetComponent->TutorialWidgetClass = TutorialWidgetComponentClass->GetDefaultObject<UTutorialWidgetComponent>()->TutorialWidgetClass;
    TutorialWidgetComponent->TutorialInputMappingContext = TutorialWidgetComponentClass->GetDefaultObject<UTutorialWidgetComponent>()->TutorialInputMappingContext;
    TutorialWidgetComponent->CloseWidgetAction = TutorialWidgetComponentClass->GetDefaultObject<UTutorialWidgetComponent>()->CloseWidgetAction;
}

void ATutorialTrigger::Action()
{
    TutorialWidgetComponent->ShowTutorial();
}

void ATutorialTrigger::DestroyTrigger()
{
    Destroy();
}
