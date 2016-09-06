// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "HeartRateMonitor.h"

AHeartRateMonitor::AHeartRateMonitor()
{
	AudioLoop = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioLoop"));
	AudioLoop->AttachTo(RootComponent);

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

void AHeartRateMonitor::SetCanCarry(bool A)
{
	Super::SetCanCarry(A);
	EnableSoundLoop();
}

void AHeartRateMonitor::EnableSoundLoop()
{
	if (LoopSound)
	{
		AudioLoop->SetSound(LoopSound);
		AudioLoop->Play();
	}
}
