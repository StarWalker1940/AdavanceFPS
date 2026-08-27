// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
#include "EquippableToolDefinition.h"
#include "InventoryComponent.h"
#include "EquippableToolBase.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	SkeletalMeshComp->SetupAttachment(RootComponent);
	SkeletalMeshComp->SetOnlyOwnerSee(true);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SkeletalMeshComp, FName("head"));
	CameraComp->bUsePawnControlRotation = true;

	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComp"));

}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		EnhancedSubsystem->AddMappingContext(CharectMoveContext,0);
	}
}

void AFPSCharacter::AttachTool(UEquippableToolDefinition* ToolDefinition)
{
	if (!IsToolAreadyEquip(ToolDefinition))
	{
		AEquippableToolBase* ToolToEquiped = GetWorld()->SpawnActor< AEquippableToolBase>(ToolDefinition->ToolAsset, this->GetTransform());

		FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, true);

		ToolToEquiped->AttachToActor(this, AttachmentRules);
		ToolToEquiped->AttachToComponent(SkeletalMeshComp, AttachmentRules, FName(TEXT("HandGrip_R")));
		//TODO  FName FString FText互相转化
	}
}

bool AFPSCharacter::IsToolAreadyEquip(UEquippableToolDefinition* ToolDefinition)
{
	for (UEquippableToolDefinition* InventoryItem : InventoryComp->ToolInventory)
	{
		if (ToolDefinition->ID == InventoryItem->ID)
			return true;
	}
	return false;
}

void AFPSCharacter::Move(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Log, TEXT("%s Moving"), *FString(__FUNCTION__));
	const FVector2D MoveVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MoveVector.Y);
		AddMovementInput(GetActorRightVector(), MoveVector.X);
	}
}

void AFPSCharacter::LookAt(const FInputActionValue& Value)
{
	const FVector2D LookAtVector = Value.Get<FVector2D>();

	if (Controller)
	{
		AddControllerYawInput(LookAtVector.X);
		AddControllerPitchInput(LookAtVector.Y);
	}
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	UEnhancedInputComponent* EnhancedComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedComp->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);
	EnhancedComp->BindAction(LookAtAction, ETriggerEvent::Triggered, this, &AFPSCharacter::LookAt);
}

