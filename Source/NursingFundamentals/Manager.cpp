// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "Manager.h"


// Sets default values
AManager::AManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AManager::BeginPlay()
{
	Super::BeginPlay();
	
	SetupAssessmentTriggers(AssessmentInfo);
}

// Called every frame
void AManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AManager::EnableAssessments(bool bEnable)
{
	for (AAssessmentTrigger* Trigger : AssessmentTriggers)
	{
		if (Trigger)
		{
			UE_LOG(LogTemp, Warning, TEXT("Enabled Assessment Trigger: %d"), bEnable);
			Trigger->EnableCollision(bEnable);
		}
	}
}

