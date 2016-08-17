// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Teleporter.h"
#include "TeleportManager.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API ATeleportManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Spanws all Teleporters
	void SpawnTeleporters();

	//Spawns a specific Teleporter
	void SpawnTeleporter(int32 TeleporterNum, bool bEnabled = true);
	void SetDisabledTeleporter(ATeleporter* NewTeleporter);

	void SetTutorial(bool bEnable);

protected:
	ATeleporter* DisabledTeleporter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		AActor* TutorialManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TSubclassOf<ATeleporter> TeleporterBP;

	TArray<FVector> TeleportLocations;
	bool bTutorial;
};
