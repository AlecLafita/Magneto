#pragma once

#include "GameFramework/Actor.h"
#include "Kismet/KismetMathLibrary.h"

namespace transformationUtils
{
	/**
	 * Gets the transform to convert from aOrigin actor space to aDestiny actor space.
	 * @param aResult Where the transform will be placed.
	 */
	inline void GetSpaceTransform(FTransform& aResult, const AActor& aOrigin, const AActor& aDestiny)
	{
		aResult = UKismetMathLibrary::InvertTransform(aDestiny.GetTransform()) * aOrigin.GetTransform();
	}
}