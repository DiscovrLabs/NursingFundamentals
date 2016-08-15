// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "DiscovrGameInstance.h"
#include "TeleportManager.h"
#include "TextController.h"
#include "ChangingActor.h"
#include "TutorialManager.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API ATutorialManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATutorialManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// TeleportManager calls this to inform TutorialManager that player teleported. TutorialManager returns whether or not to enable the previous teleporter
	bool PlayerTeleported();

	// Stethoscope calls this to infrom TutorialManager that the player has picked up or dropped the stethoscope
	UFUNCTION(BlueprintCallable, Category = "Tutorial")
		void StethoscopeDropped(bool bDropped);

protected:
	void GamestateIncrement();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ATeleportManager* TeleportManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		ATextController* TextController;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		AChangingActor* Stethoscope;

	TArray<FString> TutorialText;

	int32 Gamestate;
	int32 TimesTeleported; // Number of times the player teleported
};
