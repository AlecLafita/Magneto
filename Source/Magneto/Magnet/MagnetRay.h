#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagnetRay.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class MAGNETO_API AMagnetRay : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagnetRay();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& ShootDirection);
	void StopFire();

	UPROPERTY(VisibleDefaultsOnly, Category = Ray)
	USphereComponent* mCollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* mProjectileMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Ray)
	UStaticMeshComponent* mMeshComponent;
};
