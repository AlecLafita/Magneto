#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "MagnetedActorMovementComponent.generated.h"

/**
 *  Component that handles the movement of an actor affected by the magnet force.
 */
UCLASS()
class MAGNETO_API UMagnetedActorMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
	
public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
