// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractableObject.h"
#include "DiscovrPawn.h"
#include "Teleporter.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API ATeleporter : public AActor, public IInteractableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleporter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// InteractableObject interface functions
	virtual void ClickButton() override;
	virtual void SetHovered(bool bHovered) override;

	void EnableTeleporter(bool Enable);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visibility")
		UBillboardComponent* Billboard;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		bool bEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		AActor* TeleportManager;

	ADiscovrPawn* Player;
};
