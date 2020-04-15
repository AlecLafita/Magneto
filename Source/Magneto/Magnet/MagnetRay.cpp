#include "MagnetRay.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AMagnetRay::AMagnetRay()
{
	PrimaryActorTick.bCanEverTick = true;

	mCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	mCollisionComponent->InitSphereRadius(15.0f);
	mCollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("MagnetProjectile"));
	mCollisionComponent->OnComponentHit.AddDynamic(this, &AMagnetRay::OnHit);
	RootComponent = mCollisionComponent;

	mMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	mMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	mMeshComponent->AttachToComponent(mCollisionComponent, FAttachmentTransformRules::KeepRelativeTransform);

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

void AMagnetRay::BeginPlay()
{
	Super::BeginPlay();
}

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

void AMagnetRay::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	//TODO can start moving the hit object
	StopFire();
}
