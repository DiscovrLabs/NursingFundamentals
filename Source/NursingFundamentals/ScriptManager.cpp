// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "ScriptManager.h"


// Sets default values
AScriptManager::AScriptManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AScriptManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScriptManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

