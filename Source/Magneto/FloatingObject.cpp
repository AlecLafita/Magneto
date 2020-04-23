#include "FloatingObject.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"

// Sets default values
AFloatingObject::AFloatingObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mVisualMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mVisualMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AFloatingObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator Rotation = GetActorRotation();
	Rotation.Yaw += DeltaTime * RotationSpeed;
	SetActorRotation(Rotation);
}

