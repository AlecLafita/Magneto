#include "Magnet.h"
#include "MagnetRay.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMagnet::AMagnet()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mMeshComponent;
}

// Called when the game starts or when spawned
void AMagnet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMagnet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
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
	mRay->Stop();
}

void AMagnet::RestartRay()
{
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
	mRay->SetActorRelativeLocation(BoxExtent);
}