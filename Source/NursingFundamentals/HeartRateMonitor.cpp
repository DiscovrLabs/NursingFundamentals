// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "HeartRateMonitor.h"

AHeartRateMonitor::AHeartRateMonitor()
{
	bHasIncremented = false;
}

bool AHeartRateMonitor::SetCarried(bool bIsCarried, UGrabComponent* CarryingHand, bool bLeftHand)
{
	if (bCanCarry)
	{
		if (!bIsCarried)
		{
			if (!bHasIncremented)
			{
				Manager->GamestateIncrement();
				bHasIncremented = true;
			}
		}
	}
	
	return Super::SetCarried(bIsCarried, CarryingHand, bLeftHand);
}