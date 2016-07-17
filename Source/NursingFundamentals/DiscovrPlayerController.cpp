// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "DiscovrPlayerController.h"

// Called when the game starts or when spawned
void ADiscovrPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bLGrabbing = bRGrabbing = false;

	Player = Cast<ADiscovrPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
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
}

void ADiscovrPlayerController::LSelect()
{
	Player->LeftPalm->GrabItem();
	Player->SetGrabbing(true, true);
	bLGrabbing = true;
}

void ADiscovrPlayerController::RSelect()
{

	Player->RightPalm->GrabItem();
	Player->SetGrabbing(true, false);
	bRGrabbing = true;
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