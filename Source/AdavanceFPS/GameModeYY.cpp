// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeYY.h"

void AGameModeYY::StartPlay()
{
	Super::StartPlay();

	UE_LOG(LogTemp, Log, TEXT("%s running"), *FString(__FUNCTION__));
}
