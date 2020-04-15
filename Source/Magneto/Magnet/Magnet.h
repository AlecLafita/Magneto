#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Magnet.generated.h"

class AMagnetRay;

UCLASS()
class MAGNETO_API AMagnet : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMagnet();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void PostInitProperties() override;

	UFUNCTION()
	void Fire(const FVector& aDestinationPoint);
	
	UFUNCTION()
	void StopFire();

	UPROPERTY(EditDefaultsOnly, Category = Magnet)
	TSubclassOf<class AMagnetRay> mRayClass;

	UPROPERTY(VisibleDefaultsOnly, Category = Magnet)
	UStaticMeshComponent* mMeshComponent;

private:
	UPROPERTY()
	AMagnetRay*		mRay;

	void RestartRay();
};
