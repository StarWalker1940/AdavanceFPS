// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "FPSCharacter.generated.h"

class UInputMappingContext;
class UInputAction;
class UCameraComponent;

class UInventoryComponent;
class AEquippableToolBase;
class UEquippableToolDefinition;


UCLASS()
class ADAVANCEFPS_API AFPSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputMappingContext> CharectMoveContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> LookAtAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UInputAction> UseAction;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr< UInventoryComponent> InventoryComp;

	UPROPERTY()
	TObjectPtr<AEquippableToolBase> EquipedTool;


	UFUNCTION()
	void AttachTool(UEquippableToolDefinition* ToolDefinition);

	UFUNCTION()
	bool IsToolAreadyEquip(UEquippableToolDefinition* ToolDefinition);

	void Move(const FInputActionValue& Value);

	void LookAt(const FInputActionValue& Value);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void GiveItem(UItemDefinition* ItemDefinition);
	
};
