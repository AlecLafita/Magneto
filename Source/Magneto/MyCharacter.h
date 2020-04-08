#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class AMagnet;

UCLASS()
class MAGNETO_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCameraComponent* mCamera;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* mFPMesh;

	UPROPERTY(EditDefaultsOnly, Category = Magnet)
	TSubclassOf<class AMagnet> mMagnetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector mMagnetOffset;

	void MoveForward(float aValue);
	void MoveRight(float aValue);

	void StartJumping();
	void StopJumping();

	void CreateMagnet();
};
