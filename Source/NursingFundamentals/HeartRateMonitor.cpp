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
		if (bIsCarried)
		{
			//AudioComp->Play();
			CarryingHand->AttachObject(this, true);
			AttachedHand = CarryingHand;
		}
		else
		{
			CarryingHand->AttachObject(this, false);
			AttachedHand = NULL;
			if (!bHasIncremented)
			{
				Manager->GamestateIncrement();
				bHasIncremented = true;
			}
		}
		return true;
	}
	else
	{
		return false;
	}

}