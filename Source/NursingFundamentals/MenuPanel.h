// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ClickableWidgetContainer.h"
#include "Manager.h"
#include "RolodexMenu.h"
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

	// Called to enable the menu or go up in the hierarchy of the menu
	bool ClickMenuButton(); // Returns false if menu is disabled and true if menu is enabled after the changes

	// Called to enable or disable a set of UI Elements
	void EnableUISet(bool bEnable, int32 Set); // if Set = 0 then MainContainers, if Set = 1 then SecContainers, if Set = 2 then TerContainers

	void TurnRolodex(bool bRotateDown);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Basic")
		AManager* Manager;

	void EnableMode(int32 Mode);

	/**************************************************************************
		* MAIN MENU
	**************************************************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Main Menu")
		TArray<AClickableWidgetContainer*> MainClickableContainers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Main Menu")
		TSubclassOf<AClickableWidgetContainer> ClickableContainerBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Main Menu")
		TArray<UTexture2D*> MainImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Main Menu")
		TArray<FString> MainNames;

	TArray<FVector2D> MainClickableContainersLocations;
	int32 MainContainerMode; // -1 = Not Visible, 0 = Not Selected, 1 = Communication, 2 = Assessment, 3 = Intervention

	UFUNCTION(BlueprintImplementableEvent, Category = "UI | Main Menu")
		void SetupClickableWidgets(const TArray<UTexture2D*> &_MainImages, const TArray<FString> &_MainText, const TArray<FString> &_SecondaryText);

	/**************************************************************************
		* COMMUNICATION MENU
	**************************************************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Secondary Menu")
		TArray<AClickableWidgetContainer*> SecClickableContainers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Secondary Menu")
		TSubclassOf<ARolodexMenu> RolodexMenuBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Secondary Menu")
		TArray<UTexture2D*> SecImages;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Secondary Menu")
		TArray<FString> SecNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Secondary Menu")
		TArray<FString> TextArray1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Secondary Menu")
		TArray<FString> TextArray2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Secondary Menu")
		TArray<FString> TextArray3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI | Secondary Menu")
		TArray<FString> TextArray4;

	ARolodexMenu* RolodexMenu;
	TArray<FVector2D> SecClickableContainersLocations;
	int32 SecContainerMode; // 0 = Not Selected, 4 = Educate Patient, 5 = Current Illness, 6 = Medical History, 7 = Orientation
	int32 HierarchyLevel; // The level of the hierarchy of the menu the player is currently using. -1 = MenuDisabled, 0 = Main, 1 = Sec, 2 = Tert
};
