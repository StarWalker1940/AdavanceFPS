// Fill out your copyright notice in the Description page of Project Settings.


#include "DartLauncher.h"
#include "FPSCharacter.h"
#include "EnhancedInputComponent.h"

void ADartLauncher::Use()
{
	UE_LOG(LogTemp, Log, TEXT("__FUNCTION__"));
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
