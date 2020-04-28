#include "MagnetedActorMovementComponent.h"

void UMagnetedActorMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (UpdatedComponent && !ShouldSkipUpdate(DeltaTime))
	{
		FHitResult Hit;
		SafeMoveUpdatedComponent(FVector(0,0,-1*DeltaTime*200), UpdatedComponent->GetComponentRotation(), true, Hit);
	}
}
