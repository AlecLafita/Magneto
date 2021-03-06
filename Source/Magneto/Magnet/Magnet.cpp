#include "Magnet.h"
#include "MagnetRay.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"

AMagnet::AMagnet()
{
	PrimaryActorTick.bCanEverTick = true;

	mMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mMeshComponent;
}

void AMagnet::BeginPlay()
{
	Super::BeginPlay();
}

void AMagnet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMagnet::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMagnet::PostInitProperties()
{
	Super::PostInitProperties();
	UWorld* World = GetWorld();
	if (mRayClass != nullptr && World != nullptr)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		mRay = World->SpawnActor<AMagnetRay>(mRayClass, SpawnParams);
		mRay->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		mRay->SetActorHiddenInGame(true);
	}
}

void AMagnet::Fire(const FVector& aDestinationPoint)
{
	mRay->SetActorHiddenInGame(false);
	RestartRay();
	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(mRay->GetActorLocation(), aDestinationPoint);
	mRay->SetActorRotation(LookAt);
	mRay->FireInDirection(LookAt.Vector());
}

void AMagnet::StopFire()
{
	mRay->SetActorHiddenInGame(true);
	mRay->StopFire();
}

void AMagnet::RestartRay()
{
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
	//TODO add projectile size. Also this does not get the magnet size at all
	mRay->SetActorRelativeLocation(FVector(BoxExtent.X, 0.0f, 0.0f));
}