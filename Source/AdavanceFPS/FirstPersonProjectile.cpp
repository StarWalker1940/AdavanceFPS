// Fill out your copyright notice in the Description page of Project Settings.


#include "FirstPersonProjectile.h"
#include "GameFramework\ProjectileMovementComponent.h"
#include "Components\SphereComponent.h"


// Sets default values
AFirstPersonProjectile::AFirstPersonProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	check(SphereComp != nullptr);

	RootComponent = SphereComp;
	SphereComp->InitSphereRadius(5.0f);
	SphereComp->SetCollisionProfileName("Projectile");
	SphereComp->OnComponentHit.AddDynamic(this,&AFirstPersonProjectile::OnHit);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	check(StaticMeshComp != nullptr);
	StaticMeshComp->SetupAttachment(RootComponent);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComp"));
	check(ProjectileMovementComp != nullptr);
	
	ProjectileMovementComp->UpdatedComponent = RootComponent;
	ProjectileMovementComp->InitialSpeed = 3000.0f;
	ProjectileMovementComp->MaxSpeed = 3000.0f;
	ProjectileMovementComp->bRotationFollowsVelocity = true;
	ProjectileMovementComp->Bounciness = 0.2f;
	ProjectileMovementComp->Friction = 0.8f;

	InitialLifeSpan = LifeSpan;
}

// Called when the game starts or when spawned
void AFirstPersonProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFirstPersonProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * PhysicForce, GetActorLocation());
		Destroy();
	}
}

// Called every frame
void AFirstPersonProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

