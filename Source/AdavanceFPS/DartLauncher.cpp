// Fill out your copyright notice in the Description page of Project Settings.


#include "DartLauncher.h"
#include "FPSCharacter.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "FirstPersonProjectile.h"

void ADartLauncher::Use()
{
	UE_LOG(LogTemp, Log, TEXT("__FUNCTION__"));

	UWorld* World = GetWorld();
	check(ProjectileClass != nullptr);
	if (World!=nullptr)
	{
		FVector TargetLocation = OwningCharacter->GetCameraTargetLocation();

		FVector MuzzleLocation = SkeletalMeshComp->GetSocketLocation(TEXT("Muzzle"));
		FRotator SpawnRotator = UKismetMathLibrary::FindLookAtRotation(MuzzleLocation, TargetLocation);

		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
		World->SpawnActor<AFirstPersonProjectile>(ProjectileClass, MuzzleLocation, SpawnRotator, SpawnParameters);
	}
}

void ADartLauncher::BindInputAction(const UInputAction* ActionToBind)
{
	UE_LOG(LogTemp, Log, TEXT("__FUNCTION__"));
	if (APlayerController* PControl = Cast<APlayerController>(OwningCharacter->GetController()))
	{
		UEnhancedInputComponent* EnhancedComp = Cast<UEnhancedInputComponent>(PControl->InputComponent);
		if (EnhancedComp)
		{
			EnhancedComp->BindAction(ActionToBind, ETriggerEvent::Triggered, this, &ADartLauncher::Use);
		}
	}
	
}
