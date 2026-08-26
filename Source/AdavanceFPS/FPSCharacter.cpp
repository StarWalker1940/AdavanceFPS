// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSCharacter.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Camera/CameraComponent.h"
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

