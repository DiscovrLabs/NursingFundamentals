// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "GrabbablePhysicsActor.h"

AGrabbablePhysicsActor::AGrabbablePhysicsActor()
{
	//PrimaryActorTick.TickGroup = TG_DuringPhysics;

	ActorMesh->SetSimulatePhysics(true);
	ActorMesh->SetEnableGravity(true);

	//MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	//MovementComponent->SetUpdatedComponent(ActorMesh);

	bFirstFrame = false;
	PreviousPos = FVector::ZeroVector;
}

void AGrabbablePhysicsActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bCalcPhysics)
	{
		FVector CurrentPos = GetActorLocation();
		FVector CurrentDir = (CurrentPos - PreviousPos) / DeltaSeconds;
		float CurrentSpeed = CurrentDir.Size();
		CurrentDir.Normalize();

		if (bFirstFrame)
		{
			AvgSpeed = CurrentSpeed;
			AvgDirection = CurrentDir;
			bFirstFrame = false;
		}
		else
		{
			AvgDirection = FMath::Lerp(AvgDirection, CurrentDir, 0.5f);
			AvgSpeed = FMath::Lerp(AvgSpeed, CurrentSpeed, 0.5f);
		}

		PreviousPos = CurrentPos;
	}

	if (bResetPending)
	{
		Destroy();
	}
}

bool AGrabbablePhysicsActor::SetCarried(bool bIsCarried, UGrabComponent * CarryingHand, bool bLeftHand)
{
	if (bIsCarried)
	{
		AudioComp->Play();
		ActorMesh->SetSimulatePhysics(false);
		AvgSpeed = 0.0f;
		AvgDirection = FVector::ZeroVector;
		PreviousPos = GetActorLocation();
		bCalcPhysics = true;
		bFirstFrame = true;
	}

	bool bGrabbed = Super::SetCarried(bIsCarried, CarryingHand, bLeftHand);

	if (!bIsCarried)
	{
		ActorMesh->SetSimulatePhysics(true);
		bCalcPhysics = false;
		AddVelocity(AvgDirection * AvgSpeed);
	}

	if (!bGrabbed)
	{
		ActorMesh->SetSimulatePhysics(true);
		bCalcPhysics = false;
	}

	return bGrabbed;
}

void AGrabbablePhysicsActor::ResetActor()
{
	bResetPending = true;
}

void AGrabbablePhysicsActor::AddVelocity(FVector Velocity)
{
	ActorMesh->SetPhysicsLinearVelocity(Velocity);
}