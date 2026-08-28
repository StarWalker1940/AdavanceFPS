// Fill out your copyright notice in the Description page of Project Settings.


#include "EquippableToolBase.h"
#include "FPSCharacter.h"
//#include "InputMappingContext.h"

// Sets default values
AEquippableToolBase::AEquippableToolBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComp"));
	ensure(SkeletalMeshComp != nullptr);
}

// Called when the game starts or when spawned
void AEquippableToolBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEquippableToolBase::Use()
{
}

void AEquippableToolBase::BindInputAction(const UInputAction* ActionToBind)
{
}

// Called every frame
void AEquippableToolBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

