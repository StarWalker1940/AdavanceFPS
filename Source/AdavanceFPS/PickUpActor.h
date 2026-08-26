// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/ItemData.h"
#include "Data/ItemDefinition.h"
#include "PickUpActor.generated.h"


class UItemDefinition;
class USphereComponent;

UCLASS()
class ADAVANCEFPS_API APickUpActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APickUpActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditInstanceOnly, Category = "PickUp | Item Table")
	FName PickUpItemID;

	UPROPERTY(EditInstanceOnly, Category = "PickUp | Item Table")
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditInstanceOnly, Category = "PickUp | ItemDifinition")
	TObjectPtr<UItemDefinition> ReferenceItem;

	UPROPERTY(VisibleDefaultsOnly, Category = "PickUp | Mesh")
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;

	UPROPERTY(EditAnywhere, Category = "PickUp | Collision")
	TObjectPtr<USphereComponent> SphereComponent;

	FTimerHandle RespawnHandle;

	UPROPERTY(EditAnywhere, Category = "PickUp | Respawn")
	bool bShouldRespawn = true;

	UPROPERTY(EditAnywhere, Category = "PickUp | Respawn")
	float RespawnTime = 4.0f;

	bool bIsPickedUp = false;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void InitializePickUp();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	
};
