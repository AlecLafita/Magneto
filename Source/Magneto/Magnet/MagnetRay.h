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
	AMagnetRay();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void FireInDirection(const FVector& ShootDirection);
	void StopFire();

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(VisibleDefaultsOnly, Category = Ray)
	USphereComponent* mCollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = Movement)
	UProjectileMovementComponent* mProjectileMovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Ray)
	UStaticMeshComponent* mMeshComponent;

	DECLARE_EVENT_OneParam(AMagnetRay, FEventObjectGrabbed, AActor*);
	FEventObjectGrabbed EventObjectGrabbed;
};
