// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/ItemDefinition.h"
#include "EquippableToolDefinition.generated.h"

class UInputMappingContext;
class AEquippableToolBase;
/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class ADAVANCEFPS_API UEquippableToolDefinition : public UItemDefinition
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf< AEquippableToolBase> ToolAsset;

protected:
	virtual UEquippableToolDefinition* CreateItemCopy() const override;
	
};
