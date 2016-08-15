// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "InteractableObject.h"
#include "Components/WidgetComponent.h"
#include "WidgetContainer.h"
#include "ClickableWidgetContainer.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API AClickableWidgetContainer : public AWidgetContainer, public IInteractableObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClickableWidgetContainer();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// InteractableObject interface functions
	virtual void ClickButton() override;
	virtual void SetHovered(bool bHovered) override;

	// Functionality for setting up during runtime
	virtual void DisableContainer();
	void EnableCollision(bool bEnable);
	void SetStartLocation(FVector Start);

	FVector LocalOffset;
	int32 ContainerNum;

	AActor* ParentPanel;

protected:
	// Base values for actor to move
	FVector StartScale;
	FVector EndScale;
	FVector StartLocation;
	FVector EndLocation;
	float Alpha;

	bool bChangeDirection;
	bool bChangingSize;
	bool bClickedOn;

	// Helper function to modify blueprint widget
	UFUNCTION(BlueprintImplementableEvent, Category = "WidgetData")
		void SetWidgetHovered(bool bHovered);

//	AUIManager* Manager;
};
