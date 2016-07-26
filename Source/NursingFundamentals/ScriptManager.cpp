// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "GrabbableActor.h"
#include "ScriptManager.h"


// Sets default values
AScriptManager::AScriptManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Gamestate = 0;
}

// Called when the game starts or when spawned
void AScriptManager::BeginPlay()
{
	Super::BeginPlay();
	for (AActor* Actor : GrabbableActors)
	{
		Cast<AGrabbableActor>(Actor)->SetManager(this);
	}
}

// Called every frame
void AScriptManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AScriptManager::GamestateIncrement()
{
	Gamestate++;

	switch (Gamestate)
	{
	case 0:
		break;
	default:
		Cast<AGrabbableActor>(GrabbableActors[Gamestate])->SetCanCarry(true);
		break;
	}
}

