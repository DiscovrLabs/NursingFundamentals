// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "ClickableActor.h"

AClickableActor::AClickableActor()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(Mesh);
}

bool AClickableActor::SetCarried(bool bIsCarried, UGrabComponent* CarryingHand, bool bLeftHand)
{
	if (bIsCarried && !bSwapped)
	{
		Mesh->SetSkeletalMesh(NewMesh, false);
		bSwapped = true;
		Manager->GamestateIncrement();
	}
	return false;
}