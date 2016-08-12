// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GrabbablePhysicsActor.h"
#include "HeartRateMonitor.generated.h"

/**
 * 
 */
UCLASS()
class NURSINGFUNDAMENTALS_API AHeartRateMonitor : public AGrabbablePhysicsActor
{
	GENERATED_BODY()
	
public:
	AHeartRateMonitor();

	bool SetCarried(bool bIsCarried, UGrabComponent* CarryingHand, bool bLeftHand) override;
	
protected:
	bool bHasIncremented;
};
