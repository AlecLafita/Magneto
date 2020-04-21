#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MagnetRay.h"
#include "Magnet.generated.h"

class AMagnetRay;

UCLASS()
class MAGNETO_API AMagnet : public APawn
{
	GENERATED_BODY()

public:
	AMagnet();
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

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

	UFUNCTION()
	void MoveItemZAxis(float aValue);
	UFUNCTION()
	void MoveItemYAxis(float aValue);

	UFUNCTION()
	void OnObjectGrabbed(AActor* aGrabbedObject);

private:
	UPROPERTY()
	AMagnetRay*		mRay;

	UPROPERTY()
	AActor*			mGrabbedObject;

	void RestartRay();
};
