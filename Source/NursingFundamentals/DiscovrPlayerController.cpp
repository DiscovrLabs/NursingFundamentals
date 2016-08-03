// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "DiscovrPlayerController.h"

// Called when the game starts or when spawned
void ADiscovrPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bLGrabbing = bRGrabbing = bMenuEnabled = false;

	HUD = Cast<ADiscovrHUD>(GetHUD());
	Player = Cast<ADiscovrPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	TArray<AActor*> TempArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMenuPanel::StaticClass(), TempArray);
	MenuPanel = Cast<AMenuPanel>(TempArray[0]);
}

void ADiscovrPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ADiscovrPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LSelect", IE_Pressed, this, &ADiscovrPlayerController::LSelect);
	InputComponent->BindAction("LSelect", IE_Released, this, &ADiscovrPlayerController::LDrop);
	InputComponent->BindAction("RSelect", IE_Pressed, this, &ADiscovrPlayerController::RSelect);
	InputComponent->BindAction("RSelect", IE_Released, this, &ADiscovrPlayerController::RDrop);
	InputComponent->BindAction("Menu", IE_Pressed, this, &ADiscovrPlayerController::ToggleMenu);
}

void ADiscovrPlayerController::LSelect()
{
	if (!bMenuEnabled)
	{
		Player->LeftPalm->GrabItem();
		Player->SetGrabbing(true, true);
		bLGrabbing = true;
	}
}

void ADiscovrPlayerController::RSelect()
{
	if (bMenuEnabled)
	{
		HUD->Click();
	}
	else
	{
		Player->RightPalm->GrabItem();
		Player->SetGrabbing(true, false);
		bRGrabbing = true;
	}
}

void ADiscovrPlayerController::LDrop()
{
	Player->LeftPalm->DropItem();
	Player->SetGrabbing(false, true);
	bLGrabbing = false;
}

void ADiscovrPlayerController::RDrop()
{
	Player->RightPalm->DropItem();
	Player->SetGrabbing(false, false);
	bRGrabbing = false;
}

void ADiscovrPlayerController::ToggleMenu()
{
	if (!bRGrabbing && !bLGrabbing)
	{
		if (bMenuEnabled)
		{
			DisableRLaser();
			MenuPanel->EnableClickableContainers(false);
			bMenuEnabled = false;
		}
		else
		{
			EnableRLaser();
			MenuPanel->EnableClickableContainers(true);
			bMenuEnabled = true;
		}
	}
}

void ADiscovrPlayerController::EnableRLaser()
{
	HUD->EnableLaser(true);
	Player->SetPointing(true, false);
}

void ADiscovrPlayerController::DisableRLaser()
{
	HUD->EnableLaser(false);
	Player->SetPointing(false, false);
}