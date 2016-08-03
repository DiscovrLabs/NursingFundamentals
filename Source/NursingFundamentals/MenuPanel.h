// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ClickableWidgetContainer.h"
#include "MenuPanel.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API AMenuPanel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMenuPanel();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void ContainerClicked(int32 ContainerNum);
	void EnableClickableContainers(bool bEnable);

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
		void SetupClickableWidgets(const TArray<UTexture2D*> &_Images);

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		//TArray<AButtonCollider*> Buttons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TArray<AClickableWidgetContainer*> ClickableContainers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<AClickableWidgetContainer> ClickaleContainerBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TArray<UTexture2D*> ButtonImages;

	TArray<FVector2D>  ClickableContainersLocations;

	//void EnableButtons(bool bEnable);
};
