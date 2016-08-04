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

	void SetDisabledTeleporter(ATeleporter* NewTeleporter);

protected:
	ATeleporter* DisabledTeleporter;
};
