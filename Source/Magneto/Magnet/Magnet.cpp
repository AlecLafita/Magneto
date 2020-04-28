#include "Magnet.h"
#include "MagnetRay.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Magnet/MagnetedActorMovementComponent.h"

#include "DrawDebugHelpers.h"

AMagnet::AMagnet() :
	mRay(nullptr),
	mGrabbedObject(nullptr)
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
		mRay->EventObjectGrabbed.AddUObject(this, &AMagnet::OnObjectGrabbed);
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
	if (mGrabbedObject != nullptr)
	{
		auto GrabbedObjectMovementComponent = mGrabbedObject->FindComponentByClass<UMagnetedActorMovementComponent>();
		if (GrabbedObjectMovementComponent != nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("REMOVING MOEVEMTN COMPONENT"));
			GrabbedObjectMovementComponent->UnregisterComponent();
			mGrabbedObject->RemoveInstanceComponent(GrabbedObjectMovementComponent);
		}
		//TArray<UMagnetedActorMovementComponent*> GrabbedObjectMovementComponents;
		//mGrabbedObject->GetComponents(GrabbedObjectMovementComponents);
	// 	for (const auto GrabbedObjectMovementComponents : GrabbedObjectMovementComponents)
	// 	{
	// 		mGrabbedObject->RemoveInstanceComponent(GrabbedObjectMovementComponents);
	// 	}
		mGrabbedObject = nullptr;
	}

	//TODO this should also be done when colliding
	mRay->SetActorHiddenInGame(true);
	mRay->StopFire();
}

void AMagnet::MoveItemZAxis(float aValue)
{
	AddForceOnGrabbedObject(FVector(0.f, 0.f, aValue));
}

void AMagnet::MoveItemYAxis(float aValue)
{
	AddForceOnGrabbedObject(FVector(0.f, aValue, 0.f));
}

void AMagnet::OnObjectGrabbed(AActor* aGrabbedObject)
{
	UE_LOG(LogTemp, Warning, TEXT("OBJECT GRAABED"));
	mGrabbedObject = aGrabbedObject;
	auto MagnetedMovementComponent = NewObject<UMagnetedActorMovementComponent>(mGrabbedObject, TEXT("MagnetedMovement"));
	if (MagnetedMovementComponent != nullptr)
	{
		mGrabbedObject->AddInstanceComponent(MagnetedMovementComponent);
		MagnetedMovementComponent->RegisterComponent();
	}
}

void AMagnet::RestartRay()
{
	FVector Origin;
	FVector BoxExtent;
	GetActorBounds(true, Origin, BoxExtent);
	//TODO add projectile size. Also this does not get the magnet size at all
	mRay->SetActorRelativeLocation(FVector(BoxExtent.X, 0.0f, 0.0f));
}

void AMagnet::AddForceOnGrabbedObject(FVector aForceDirection)
{
	if (mGrabbedObject != nullptr && aForceDirection != FVector::ZeroVector)
	{
		//TODO this should be made on camera space instead of the magnet space
		FVector ForceVector = GetTransform().TransformVector(aForceDirection);
		ForceVector.Normalize();
		if (mGrabbedObject->IsRootComponentMovable())
		{
			UStaticMeshComponent* GrabbedObjectMesh = Cast<UStaticMeshComponent>(mGrabbedObject->GetRootComponent());
			//GrabbedObjectMesh->AddForce(ForceVector* mMagneticForce);

			FVector Origin;
			FVector BoxExtent;
			mGrabbedObject->GetActorBounds(true, Origin, BoxExtent);
			DrawDebugDirectionalArrow(GetWorld(), Origin - ForceVector*400, Origin, 60.0f, FColor::Yellow, false, 1.f, 0, 5.0f);
		}
	}
}
