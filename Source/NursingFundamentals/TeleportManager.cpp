// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "DiscovrGameInstance.h"
#include "TutorialManager.h"
#include "TeleportManager.h"


// Sets default values
ATeleportManager::ATeleportManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TeleportLocations.Add(FVector(261.f, -91.f, 170.f));
	TeleportLocations.Add(FVector(-5.5f, 449.f, 170.f));
	TeleportLocations.Add(FVector(152.f, -248.f, 170.f));
	TeleportLocations.Add(FVector(-156.f, 302.f, 170.f));

	bTutorial = false;
}

// Called when the game starts or when spawned
void ATeleportManager::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATeleportManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

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
		SetDisabledTeleporter(Temp);
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
		DisabledTeleporter->EnableTeleporter(false);
	}
}

void ATeleportManager::SetTutorial(bool bEnable)
{
	bTutorial = bEnable;
}