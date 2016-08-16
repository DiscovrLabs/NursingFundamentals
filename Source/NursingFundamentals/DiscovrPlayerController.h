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

	// Called to set bTutorial1
	void SetTutorial1(bool bEnable);

	// Called to set bTutorial2
	void SetTutorial2(bool bEnable);

protected:
	ADiscovrPawn* Player;
	ADiscovrHUD* HUD;
	AMenuPanel* MenuPanel;

	bool bLGrabbing;
	bool bRGrabbing;
	bool bMenuEnabled;
	bool bKeepMenu;
	bool bTutorial1; // Used to stop or allow access to the menu based on the tutorial
	bool bTutorial2; // Used to stop or allow access to the health record based on the tutorial

	void ToggleMenu();
	void LSelect();
	void RSelect();
	void LDrop();
	void RDrop();
	void EnableRLaser();
	void DisableRLaser();
	void ScrollDown();
	void ScrollUp();
	void ShowHealthRecord();
};