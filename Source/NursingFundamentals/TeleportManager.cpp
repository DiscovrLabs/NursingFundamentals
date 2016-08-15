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
	if (TutorialManager)
	{
		if (DisabledTeleporter && Cast<ATutorialManager>(TutorialManager)->PlayerTeleported())
		{
			DisabledTeleporter->EnableTeleporter(true);
		}
	}
	else
	{
		if (DisabledTeleporter)
		{
			DisabledTeleporter->EnableTeleporter(true);
		}
	}
		DisabledTeleporter = NewTeleporter;
}