#include "MagnetRay.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMagnetRay::AMagnetRay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	mMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = mMeshComponent;

	mCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	mCollisionComponent->InitSphereRadius(15.0f);
	mCollisionComponent->SetupAttachment(mMeshComponent);

	mProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	mProjectileMovementComponent->SetUpdatedComponent(mCollisionComponent);
	mProjectileMovementComponent->InitialSpeed = 400.0f;
	mProjectileMovementComponent->MaxSpeed = 3000.0f;
	mProjectileMovementComponent->bRotationFollowsVelocity = true;
	mProjectileMovementComponent->bShouldBounce = true;
	mProjectileMovementComponent->Bounciness = 0.3f;
	mProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	mProjectileMovementComponent->bSimulationEnabled = false;
}

// Called when the game starts or when spawned
void AMagnetRay::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMagnetRay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMagnetRay::FireInDirection(const FVector& ShootDirection)
{
	mProjectileMovementComponent->bSimulationEnabled = true;
	mProjectileMovementComponent->Velocity = ShootDirection * mProjectileMovementComponent->InitialSpeed;
}

void AMagnetRay::StopFire()
{
	mProjectileMovementComponent->bSimulationEnabled = false;
}
