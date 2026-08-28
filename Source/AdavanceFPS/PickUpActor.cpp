// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpActor.h"
#include "FPSCharacter.h"
#include "Components/SphereComponent.h"

// Sets default values
APickUpActor::APickUpActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	check(StaticMeshComp != nullptr);

	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	check(SphereComponent != nullptr);

	SphereComponent->SetupAttachment(StaticMeshComp);
	SphereComponent->SetSphereRadius(30.0f);
}

// Called when the game starts or when spawned
void APickUpActor::BeginPlay()
{
	Super::BeginPlay();

	InitializePickUp();

	ensure(ItemDataTable != nullptr);
}

void APickUpActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorldTimerManager().ClearTimer(RespawnHandle);

	SphereComponent->OnComponentBeginOverlap.RemoveAll(this);

	Super::EndPlay(EndPlayReason);
}


void APickUpActor::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if (bIsPickedUp)
	{
		return;
	}*/

	GEngine->AddOnScreenDebugMessage(-1, 0, FColor::Yellow, TEXT("OnSphereBeginOverlap pick"));

	AFPSCharacter* Character = Cast<AFPSCharacter>(OtherActor);

	if (Character != nullptr)
	{
		bIsPickedUp = true;
		Character->GiveItem(ReferenceItem);

		SphereComponent->OnComponentBeginOverlap.RemoveAll(this);
		StaticMeshComp->SetVisibility(false);
		StaticMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if (bShouldRespawn)
		{
			GetWorldTimerManager().SetTimer(RespawnHandle, this, &APickUpActor::InitializePickUp, RespawnTime, false);
			
			UE_LOG(LogTemp, Log, TEXT("RespawnTime == %f %f"), RespawnTime, GetWorld()->GetRealTimeSeconds());
		}
	}
}

void APickUpActor::InitializePickUp()
{
	//bIsPickedUp = false;

	UE_LOG(LogTemp, Log, TEXT("InitializePickUp runningtime == %f"), GetWorld()->GetRealTimeSeconds());
	if (ItemDataTable && !PickUpItemID.IsNone())
	{
		const FItemData* ItemDataRow = ItemDataTable->FindRow<FItemData>(PickUpItemID, PickUpItemID.ToString());

		check(ItemDataRow!=nullptr);
		
		if (ReferenceItem)
		{
			UEngine::CopyPropertiesForUnrelatedObjects(ItemDataRow->ItemBase.Get(), ReferenceItem);
		}
		else
		{
			ReferenceItem = ItemDataRow->ItemBase.Get();
			ReferenceItem = ReferenceItem->CreateItemCopy();
		}
		
		

		StaticMeshComp->SetStaticMesh(ReferenceItem->WorldMesh.LoadSynchronous());
		StaticMeshComp->SetVisibility(true);

		SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickUpActor::OnSphereBeginOverlap);
	}
}

void APickUpActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	const FName ChangePropertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (ChangePropertyName == GET_MEMBER_NAME_CHECKED(APickUpActor, PickUpItemID) && ItemDataTable)
	{
		if (const FItemData* ItemDataRow = ItemDataTable->FindRow<FItemData>(PickUpItemID, PickUpItemID.ToString()))
		{
			UItemDefinition* ItemDefinition = ItemDataRow->ItemBase;

			StaticMeshComp->SetStaticMesh(ItemDefinition->WorldMesh.LoadSynchronous());
		}
	}
}

// Called every frame
void APickUpActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

