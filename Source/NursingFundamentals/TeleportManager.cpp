// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "DiscovrGameInstance.h"
#include "TutorialManager.h"
#include "TeleportManager.h"


// Sets default values
ATeleportManager::ATeleportManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	TeleportLocations.Add(FVector(-116.884834f, -112.644356f, 130.f));
	TeleportLocations.Add(FVector(-317.102051f, -91.714333f, 130.f));
	TeleportLocations.Add(FVector(-140.637268f, 152.554108f, 130.f));
	TeleportLocations.Add(FVector(302.166992f, 152.554504f, 130.f));

	bTutorial = false;
}

// Called when the game starts or when spawned
void ATeleportManager::BeginPlay()
{
	Super::BeginPlay();
}

void ATeleportManager::SpawnTeleporters()
{
	for (int i = 0; i < TeleportLocations.Num(); i++)
	{
		if (i == 0)
			SpawnTeleporter(i, false);
		else
			SpawnTeleporter(i);
	}
}

void ATeleportManager::SpawnTeleporter(int32 TeleporterNum, bool bEnabled)
{
	ATeleporter* Temp = GetWorld()->SpawnActor<ATeleporter>(TeleporterBP);
	Temp->SetActorLocation(TeleportLocations[TeleporterNum]);
	Temp->SetManager(this);

	if (!bEnabled)
		Temp->EnableTeleporter(false);
}

void ATeleportManager::SetDisabledTeleporter(ATeleporter* NewTeleporter)
{
	if (bTutorial)
	{
		if (DisabledTeleporter && Cast<ATutorialManager>(TutorialManager)->PlayerTeleported())
		{
			DisabledTeleporter->EnableTeleporter(true);
		}
		DisabledTeleporter = NewTeleporter;
	}
	else
	{
		if (DisabledTeleporter)
		{
			DisabledTeleporter->EnableTeleporter(true);
		}
		DisabledTeleporter = NewTeleporter;
	}
}

void ATeleportManager::SetTutorial(bool bEnable)
{
	bTutorial = bEnable;
}