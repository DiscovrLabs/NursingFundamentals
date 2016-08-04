// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "InteractableObject.h"
#include "GazeTrigger.h"
#include "DiscovrHUD.h"

// Called when the game starts or when spawned
void ADiscovrHUD::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ADiscovrPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	RLaserComponent = UGameplayStatics::SpawnEmitterAttached(LaserBP, Player->RLaserOrigin);
	RLaserComponent->SetVisibility(false);
	RLookingAtActor = NULL;
	RLaserStartPoint = RLaserVector = FVector::ZeroVector;
	LaserRange = 15;
	bRightEnabled = false;

	CameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	FLookingAtActor = NULL;
	FGazeStartPoint = FGazeVector = FVector::ZeroVector;
	GazeRange = 1200;
}

// Called every frame
void ADiscovrHUD::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRightEnabled)
	{
		RLaserStartPoint = Player->RLaserOrigin->GetComponentLocation();
		RLaserVector = FRotationMatrix(Player->RightHand->GetComponentRotation()).GetScaledAxis(EAxis::X);

		FHitResult ObjectHit;
		bool bHit = GetWorld()->LineTraceSingleByChannel(ObjectHit, RLaserStartPoint, RLaserVector * LaserRange + RLaserStartPoint, ECollisionChannel::ECC_Visibility);
		/*
		DrawDebugLine(
		GetWorld(),
		LaserStartPoint,
		ObjectHit.Location,
		FColor(255, 0, 0),
		false, -1, 0,
		12.333
		);*/

		if (bHit)
		{
			if (RLookingAtActor != ObjectHit.GetActor())
			{
				if (RLookingAtActor)
				{
					Cast<IInteractableObject>(RLookingAtActor)->SetHovered(false);
					RLookingAtActor = NULL;
				}
				if (ObjectHit.GetActor()->Implements<UInteractableObject>())
				{
					RLookingAtActor = ObjectHit.GetActor();
					Cast<IInteractableObject>(RLookingAtActor)->SetHovered(true);
					//Add Snap Here
				}
			}
		}
		else
		{
			if (RLookingAtActor)
			{
				Cast<IInteractableObject>(RLookingAtActor)->SetHovered(false);
				RLookingAtActor = NULL;
			}
		}

		float f = FMath::Clamp(((ObjectHit.Location - RLaserStartPoint).Size() * 0.9f), 10.f, 1000.f);
		RLaserComponent->SetBeamTargetPoint(0, RLaserVector * f + RLaserStartPoint, 0);
	}
	FGazeStartPoint = CameraManager->GetCameraLocation();
	FGazeVector = FRotationMatrix(CameraManager->GetCameraRotation()).GetScaledAxis(EAxis::X);

	FHitResult ObjectHit;
	bool bHit = GetWorld()->LineTraceSingleByChannel(ObjectHit, FGazeStartPoint, FGazeVector * GazeRange + FGazeStartPoint, ECollisionChannel::ECC_Visibility);
	/*
	DrawDebugLine(
	GetWorld(),
	LaserStartPoint,
	ObjectHit.Location,
	FColor(255, 0, 0),
	false, -1, 0,
	12.333
	);*/

	if (bHit)
	{
		if (FLookingAtActor != ObjectHit.GetActor())
		{
			if (FLookingAtActor)
			{
				Cast<IGazeTrigger>(FLookingAtActor)->SetHovered(false);
				FLookingAtActor = NULL;
			}
			if (ObjectHit.GetActor()->Implements<UGazeTrigger>())
			{
				FLookingAtActor = ObjectHit.GetActor();
				Cast<IGazeTrigger>(FLookingAtActor)->SetHovered(true);
				//Add Snap Here
			}
		}
	}
	else
	{
		if (FLookingAtActor)
		{
			Cast<IGazeTrigger>(FLookingAtActor)->SetHovered(false);
			FLookingAtActor = NULL;
		}
	}

	//float f = FMath::Clamp(((ObjectHit.Location - FGazeStartPoint).Size() * 0.9f), 10.f, 1000.f);
}

void ADiscovrHUD::EnableLaser(bool bEnable)
{

	bRightEnabled = bEnable;
	//RLaserComponent->SetVisibility(bEnable);
	if (!bEnable && RLookingAtActor != NULL)
	{
		Cast<IInteractableObject>(RLookingAtActor)->SetHovered(false);
		RLookingAtActor = NULL;
	}
}

void ADiscovrHUD::Click()
{

	if (RLookingAtActor)
	{
		Cast<IInteractableObject>(RLookingAtActor)->ClickButton();
	}
}
