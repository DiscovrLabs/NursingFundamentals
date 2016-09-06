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
			TellManager(false);
			AudioComp->Play();
			SetActorRelativeLocation(FVector::ZeroVector);
			SetActorRelativeRotation(FQuat::Identity);
			ActorMesh->SetStaticMesh(GrabbedMesh);
		}
		else
		{
			TellManager(true);
			ActorMesh->SetStaticMesh(StartMesh);
			AddVelocity(AvgDirection * AvgSpeed);
		}
	}

	return tempBool;
}
