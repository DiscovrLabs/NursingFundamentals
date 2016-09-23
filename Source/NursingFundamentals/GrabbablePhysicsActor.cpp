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

	bFirstFrame = bCalcPhysics = false;
	ResetTimer = 0.0f;
	KillZ = 10.0f;
	PreviousPos = FVector::ZeroVector;
}

void AGrabbablePhysicsActor::BeginPlay()
{
	Super::BeginPlay();

	SpawnPos = GetTransform();
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

	if (!bCalcPhysics)
	{
		if (GetActorLocation().Z < KillZ)
		{
			ResetTimer += DeltaSeconds;
			if (ResetTimer > 3.0f)
			{
				ResetTimer = 0.0f;
				ResetActor();
			}
		}
	}
}

bool AGrabbablePhysicsActor::SetCarried(bool bIsCarried, UGrabComponent * CarryingHand, bool bLeftHand)
{
	if (bCanCarry && (AttachedHand == NULL || CarryingHand == AttachedHand))
	{
		if (bIsCarried)
		{
			AudioComp->Play();
			ActorMesh->SetSimulatePhysics(false);
			AvgSpeed = ResetTimer = 0.0f;
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
	else
	{
		//Play error sound
		return false;
	}
}

void AGrabbablePhysicsActor::ResetActor()
{
	SetActorTransform(SpawnPos);
}

void AGrabbablePhysicsActor::AddVelocity(FVector Velocity)
{
	ActorMesh->SetPhysicsLinearVelocity(Velocity);
}