// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "TutorialManager.h"


// Sets default values
ATutorialManager::ATutorialManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TutorialText.Add("To Teleport to another section of the room, just gaze in the direction of the area and wait until you are there. Try moving over to the sink.");
	TutorialText.Add("Very Good, now move back to the bedside.");
	TutorialText.Add("To your side you will see your medical tray that contains all the tools you will need for this module.Try grabbing your stethoscope.");
	TutorialText.Add("Very good! You can go ahead and set that back down now.");
	TutorialText.Add("To interact with your patient you will have to indicate the interaction with your left controller, Press the left touchpad button to spawn your interaction options.");

	Gamestate = 0;
	TimesTeleported = 0;
}

// Called when the game starts or when spawned
void ATutorialManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (!Cast<UDiscovrGameInstance>(GetGameInstance())->bTutorial)
	{
		TeleportManager->SpawnTeleporters();
	}
	else
	{
		Stethoscope->SetCanCarry(false);
		TextController->SetText("Welcome to Nursing Fundamentals", TutorialText[0]);
		TeleportManager->SpawnTeleporter(0, false);
		TeleportManager->SpawnTeleporter(3);
	}
}

// Called every frame
void ATutorialManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool ATutorialManager::PlayerTeleported()
{
	TimesTeleported++;
	if (TimesTeleported == 1)
	{
		TextController->SetText("", TutorialText[1]);
		return true;
	}
	else if (TimesTeleported == 2)
	{
		TextController->SetText("", TutorialText[2]);
		GamestateIncrement();
		return false;
	}
	return false;
}

void ATutorialManager::StethoscopeDropped(bool bDropped)
{
	// If grabbed
	if (!bDropped)
	{
		TextController->SetText("", TutorialText[3]);
	}
	else
	{
		TextController->SetText("", TutorialText[4]);
		Stethoscope->SetCanCarry(false);
	}
}

void ATutorialManager::GamestateIncrement()
{
	Gamestate++;
	switch (Gamestate)
	{
	case 1:
		Stethoscope->SetCanCarry(true);
	}
}