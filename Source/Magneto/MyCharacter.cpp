#include "MyCharacter.h"
//#include "Components/StaticMeshComponent.h"
//#include "GameFramework/SpringArmComponent.h"
//#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/PlayerController.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	/*mMesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	mCamera = CreateDefaultSubobject<UCameraComponent>("Camera");

	mMesh->SetupAttachment(RootComponent);
	mSpringArm->SetupAttachment(mMesh);
	mCamera->SetupAttachment(mSpringArm);*/
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);
}

void AMyCharacter::MoveForward(float aValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, aValue);
}

void AMyCharacter::MoveRight(float aValue)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, aValue);
}
