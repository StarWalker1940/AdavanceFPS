// Fill out your copyright notice in the Description page of Project Settings.


#include "EquippableToolDefinition.h"

UEquippableToolDefinition* UEquippableToolDefinition::CreateItemCopy() const
{
	UEquippableToolDefinition* EquipItem = NewObject< UEquippableToolDefinition>(StaticClass());
	
	EquipItem->ID = this->ID;
	EquipItem->ItemType = this->ItemType;
	EquipItem->ItemText = this->ItemText;
	EquipItem->WorldMesh = this->WorldMesh;
	EquipItem->ToolAsset = this->ToolAsset;
	
	return EquipItem;
}
