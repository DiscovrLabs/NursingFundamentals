// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "DiscovrPawn.h"
#include "DiscovrHUD.generated.h"

/**
 * 
 */
UCLASS()
class NURSINGFUNDAMENTALS_API ADiscovrHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	void EnableLaser(bool bEnable);
	void Click();

protected:
	ADiscovrPawn* Player;
	APlayerCameraManager* CameraManager;

	//Right Laser
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser")
		UParticleSystem* LaserBP;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser")
		UParticleSystemComponent* RLaserComponent;
	AActor* RLookingAtActor;
	FVector RLaserStartPoint;
	FVector RLaserVector;
	float LaserRange;
	bool bRightEnabled;

	//Face Gaze
	AActor* FLookingAtActor;
	FVector FGazeStartPoint;
	FVector FGazeVector;
	float GazeRange;
};
