// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "TeleportManager.h"


// Sets default values
ATeleportManager::ATeleportManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

void ATeleportManager::SetDisabledTeleporter(ATeleporter* NewTeleporter)
{
	if (DisabledTeleporter)
	{
		DisabledTeleporter->EnableTeleporter(true);
	}
		DisabledTeleporter = NewTeleporter;
}