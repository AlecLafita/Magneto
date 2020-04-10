#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/PlayerController.h"
#include "Magnet/Magnet.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(GetCapsuleComponent());
	mCamera->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	mCamera->bUsePawnControlRotation = true;

	mFPMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPMesh"));
	mFPMesh->SetOnlyOwnerSee(true);
	mFPMesh->SetupAttachment(mCamera);
	mFPMesh->bCastDynamicShadow = false;
	mFPMesh->CastShadow = false;
	GetMesh()->SetOwnerNoSee(true);
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
	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::StartJumping);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::StopJumping);
	PlayerInputComponent->BindAction("UseMagnet", IE_Pressed, this, &AMyCharacter::InvokeMagnet);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AMyCharacter::Fire);
	PlayerInputComponent->BindAction("StopFire", IE_Released, this, &AMyCharacter::StopFire);

}

void AMyCharacter::PostInitProperties()
{
	Super::PostInitProperties();

	UWorld* World = GetWorld();
	if (mMagnetClass != nullptr && World != nullptr)
	{
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		FVector MagnetLocation = CameraLocation + FTransform(CameraRotation).TransformVector(mMagnetOffset);
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		mMagnet = World->SpawnActor<AMagnet>(mMagnetClass, MagnetLocation, CameraRotation, SpawnParams);
		mMagnet->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
		mMagnet->SetActorHiddenInGame(true);
	}
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

void AMyCharacter::StartJumping()
{
	bPressedJump = true;
}

void AMyCharacter::StopJumping()
{
	bPressedJump = false;
}

void AMyCharacter::InvokeMagnet()
{
	mMagnet->SetActorHiddenInGame(!mMagnet->bHidden);
}

void AMyCharacter::Fire()
{
	if (!mMagnet->bHidden)
	{
		mMagnet->SetActorHiddenInGame(true);
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		//TODO calculate this with the targeted object
		FVector DestinationPoint = CameraLocation + FTransform(CameraRotation).TransformVector(FVector(400.0f,0.0f,0.0f));

		mMagnet->Fire(DestinationPoint);
	}
}

void AMyCharacter::StopFire()
{
	if (!mMagnet->bHidden)
	{
		mMagnet->StopFire();
	}
}