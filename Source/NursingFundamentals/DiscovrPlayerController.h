// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "DiscovrPawn.h"
#include "DiscovrHUD.h"
#include "MenuPanel.h"
#include "DiscovrPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class NURSINGFUNDAMENTALS_API ADiscovrPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

protected:
	ADiscovrPawn* Player;
	ADiscovrHUD* HUD;
	AMenuPanel* MenuPanel;

	bool bLGrabbing;
	bool bRGrabbing;
	bool bMenuEnabled;

	void LSelect();
	void RSelect();
	void LDrop();
	void RDrop();
	void ToggleMenu();
	void EnableRLaser();
	void DisableRLaser();
};