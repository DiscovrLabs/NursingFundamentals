// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ScriptManager.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API AScriptManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AScriptManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void GamestateIncrement();
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		TArray<AActor*> GrabbableActors;

	int32 Gamestate;
};
