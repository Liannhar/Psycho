// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem/Item.h"

UItem::UItem()
{
	Mesh = CreateDefaultSubobject<UStaticMesh>("ItemMesh");
	Icon = CreateDefaultSubobject<UTexture2D>("Thumbnail");
	Name = FText::FromString("ItemName");
	Description = FText::FromString("ItemDescription");
}

void UItem::Use(APlayerCharacter* Player)
{
}
