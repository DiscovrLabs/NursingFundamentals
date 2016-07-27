// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "ChangingActor.h"

void AChangingActor::BeginPlay()
{
	Super::BeginPlay();
	StartMesh = ActorMesh->StaticMesh;
}

bool AChangingActor::SetCarried(bool bIsCarried, UGrabComponent* CarryingHand, bool bLeftHand)
{
	bool tempBool = Super::SetCarried(bIsCarried, CarryingHand, bLeftHand);
	if (tempBool)
	{
		if (bIsCarried)
		{
			ActorMesh->SetStaticMesh(GrabbedMesh);
		}
		else
		{
			ActorMesh->SetStaticMesh(StartMesh);
		}
	}

	return tempBool;
}
