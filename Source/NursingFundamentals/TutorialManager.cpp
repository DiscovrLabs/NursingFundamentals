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
	TutorialText.Add("You can have three interaction categories. Let's try a communication: Introduce yourself to the patient.");
	TutorialText.Add("Go ahead and speak out the communication you selected");
	TutorialText.Add("Now let's try an assessment. Select an Assessment from the interaction menu.");
	TutorialText.Add("Good! You will now see all the options you have to assess this patient for this particular module. Just press the trackpad to exit Assessment mode");
	TutorialText.Add("Now press the touchpad again to quit the menu.");
	TutorialText.Add("If you pause the module, you will be able to see the patient's Electronic Health Record which will give you additional details about your patient and their condition. Give it a look");
	TutorialText.Add("When you are ready to call a provider or hand off your patient, just teleport to the exit door. Try it now.");

	Gamestate = TimesTeleported = bButttonOneClicked = bButtonTwoClicked = 0;
}

// Called when the game starts or when spawned
void ATutorialManager::BeginPlay()
{
	Super::BeginPlay();
	
	// If player did not choose tutorial mode
	if (!Cast<UDiscovrGameInstance>(GetGameInstance())->bTutorial)
	{
		TeleportManager->SpawnTeleporters();
		if (TextController)
			TextController->Destroy();
		Destroy();
	}
	else
	{
		PlayerController = Cast<ADiscovrPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		if (PlayerController)
		{
			PlayerController->SetTutorial1(true);
			PlayerController->SetTutorial2(true);
		}
		if (MenuPanel)
		{
			MenuPanel->SetTutorial(true);
		}
		if (Patient)
		{
			Patient->BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
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
	else if (TimesTeleported == 3)
	{
		Cast<UDiscovrGameInstance>(GetGameInstance())->bTutorial = false;
		// Go back to menu
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
		GamestateIncrement();
	}
}

void ATutorialManager::ButtonClicked(int32 ButtonNum)
{
	if (ButtonNum == 0)
	{
		if (bButttonOneClicked && Gamestate == 2)
		{
			bButttonOneClicked = false;
			TextController->SetText("", TutorialText[7]);
			GamestateIncrement();
		}
		else if(bButtonTwoClicked)
		{
			bButtonTwoClicked = false;
			GamestateIncrement();
		}
		else
		{
			if (Gamestate == 2)
			{
				TextController->SetText("", TutorialText[5]);
				MenuPanel->EnableContianer(1, false);
			}
			else if (Gamestate == 3)
			{
				MenuPanel->EnableContianer(0, false);
			}
			else
			{
				GamestateIncrement();
			}
			MenuPanel->EnableContianer(2, false);
		}
	}
	else if (ButtonNum == 1)
	{
		bButttonOneClicked = true;
		TextController->SetText("", TutorialText[6]);
	}
	else if (ButtonNum == 2)
	{
		bButtonTwoClicked = true;
		TextController->SetText("", TutorialText[8]);
	}
	else if (ButtonNum == 99)
	{
		GamestateIncrement();
	}
}

void ATutorialManager::GamestateIncrement()
{
	Gamestate++;
	switch (Gamestate)
	{
	case 1:
		Stethoscope->SetCanCarry(true);
		break;
	case 2:
		PlayerController->SetTutorial1(false);
		break;
	case 3:
		MenuPanel->EnableContianer(0, false);
		MenuPanel->EnableContianer(1, true);
		MenuPanel->EnableContianer(2, false);
		break;
	case 4:
		MenuPanel->EnableContianer(0, false);
		MenuPanel->EnableContianer(1, false);
		MenuPanel->EnableContianer(2, false);
		TextController->SetText("", TutorialText[9]);
		break;
	case 5:
		PlayerController->SetTutorial1(true);
		PlayerController->SetTutorial2(false);
		TextController->SetText("", TutorialText[10]);
		break;
	case 6:
		PlayerController->SetTutorial2(true);
		TeleportManager->SpawnTeleporter(4);
		TextController->SetText("", TutorialText[11]);
		break;
	}
}