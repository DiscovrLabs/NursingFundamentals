// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "DiscovrPawn.h"
#include "MenuPanel.h"


// Sets default values
AMenuPanel::AMenuPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainClickableContainersLocations.Add(FVector2D(0, 7.5));
	MainClickableContainersLocations.Add(FVector2D(-4.5, 0));
	MainClickableContainersLocations.Add(FVector2D(4.5, 0));
	MainContainerMode = -1;
	HierarchyLevel = -1;

	SecClickableContainersLocations.Add(FVector2D(0, 7.5));
	SecClickableContainersLocations.Add(FVector2D(-4.5, 0));
	SecClickableContainersLocations.Add(FVector2D(4.5, 0));
	SecClickableContainersLocations.Add(FVector2D(7, 0));
	SecContainerMode = 0;
}

// Called when the game starts or when spawned
void AMenuPanel::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TempArray;
	for (int i = 0; i < MainClickableContainersLocations.Num(); i++)
	{
		TempArray.Add(GetWorld()->SpawnActor(ClickaleContainerBP));
		TempArray[i]->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, NAME_None);
		TempArray[i]->SetActorRotation(GetActorRotation());
		TempArray[i]->AddActorLocalOffset(FVector(0.f, MainClickableContainersLocations[i].X, MainClickableContainersLocations[i].Y));
		MainClickableContainers.Add(Cast<AClickableWidgetContainer>(TempArray[i]));
		MainClickableContainers[i]->LocalOffset = FVector(0.f, MainClickableContainersLocations[i].X, MainClickableContainersLocations[i].Y);
		MainClickableContainers[i]->SetStartLocation(MainClickableContainers[i]->LocalOffset);
		MainClickableContainers[i]->ContainerNum = i;
		MainClickableContainers[i]->ParentPanel = this;
	}
	SetupClickableWidgets(ButtonImages);
	this->AttachToComponent(Cast<ADiscovrPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->GetHandMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "ThumbSocket");
	EnableClickableContainers(false, 0);
	//EnableButtons(false);
}

// Called every frame
void AMenuPanel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool AMenuPanel::ClickMenuButton()
{
	// if player is in the main menu, turn it off
	if (HierarchyLevel == 0)
	{
		EnableMode(-1);
		return false;
	}
	// if menu is off or player is in the 2nd level of the menu, turn on the main level of the menu. else if player is in the 3rd level of the menu send them back to the 2nd
	if (HierarchyLevel == -1 || HierarchyLevel == 1)
	{
		EnableMode(0);
	}
	else if (HierarchyLevel == 2)
	{
		EnableMode(MainContainerMode);
	}
	return true;
}

void AMenuPanel::EnableClickableContainers(bool bEnable, int32 Set)
{
	if (bEnable)
	{
		switch (Set)
		{
		case 0:
			for (AClickableWidgetContainer* Container : MainClickableContainers)
			{
				Container->SetActorHiddenInGame(false);
				Container->EnableCollision(true);
			}
			break;
		case 1:
			for (AClickableWidgetContainer* Container : SecClickableContainers)
			{
				Container->SetActorHiddenInGame(false);
				Container->EnableCollision(true);
			}
			break;
		}
	}
	else
	{
		switch (Set)
		{
		case 0:
			for (AClickableWidgetContainer* Container : MainClickableContainers)
			{
				Container->SetActorHiddenInGame(true);
				Container->EnableCollision(false);
			}
			break;
		case 1:
			for (AClickableWidgetContainer* Container : SecClickableContainers)
			{
				Container->SetActorHiddenInGame(true);
				Container->EnableCollision(false);
			}
			break;
		}
	}
}

void AMenuPanel::ContainerClicked(int32 ContainerNum)
{
	if (Manager)
	{
		EnableMode(ContainerNum);
	}
}

void AMenuPanel::EnableMode(int32 Mode)
{
	switch (Mode)
	{
	case -1: // Not Visible
		EnableClickableContainers(false, 0);
		MainContainerMode = -1;
		HierarchyLevel = -1;
		break;
	case 0: // Not Selected
		EnableClickableContainers(true, 0);
		if(SecContainerMode != -1)
			EnableClickableContainers(false, 1);
		MainContainerMode = 0;
		HierarchyLevel = 0;
		break;
	case 1: // Communication
		EnableClickableContainers(false, 0);
		EnableClickableContainers(true, 1);
		MainContainerMode = 1;
		HierarchyLevel = 1;
		break;
	case 2: // Assessment
		Manager->EnableAssessments(true);
		MainContainerMode = 2;
		HierarchyLevel = 1;
		break;
	case 3: // Intervention
		MainContainerMode = 3;
		HierarchyLevel = 1;
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		EnableClickableContainers(false, 1);
		SecContainerMode = Mode;
		HierarchyLevel = 2;
		break;
	default:
		break;
	}
}