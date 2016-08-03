// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "MenuPanel.h"


// Sets default values
AMenuPanel::AMenuPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	float X = 100;
	float Y = 0;

	ClickableContainersLocations.Add(FVector2D(X, Y));
	ClickableContainersLocations.Add(FVector2D(0, Y));
	ClickableContainersLocations.Add(FVector2D(-X, Y));
}

// Called when the game starts or when spawned
void AMenuPanel::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TempArray;
	for (int i = 0; i < ClickableContainersLocations.Num(); i++)
	{
		TempArray.Add(GetWorld()->SpawnActor(ClickaleContainerBP));
		TempArray[i]->AttachRootComponentTo(RootComponent, NAME_None, EAttachLocation::SnapToTarget);
		TempArray[i]->SetActorRotation(GetActorRotation());
		TempArray[i]->AddActorLocalOffset(FVector(0.f, ClickableContainersLocations[i].X, ClickableContainersLocations[i].Y));
		ClickableContainers.Add(Cast<AClickableWidgetContainer>(TempArray[i]));
		ClickableContainers[i]->LocalOffset = FVector(0.f, ClickableContainersLocations[i].X, ClickableContainersLocations[i].Y);
		ClickableContainers[i]->SetStartLocation(ClickableContainers[i]->LocalOffset);
		//Cast<AModuleContainer>(ClickableContainers[i])->ParentPanelContainer = this;
	}
	SetupClickableWidgets(ButtonImages);
	//EnableButtons(false);
}

// Called every frame
void AMenuPanel::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AMenuPanel::EnableClickableContainers(bool bEnable)
{
	if (bEnable)
	{
		for (AClickableWidgetContainer* Container : ClickableContainers)
		{
			Container->EnableCollision(true);
		}
	}
	else
	{
		for (AClickableWidgetContainer* Container : ClickableContainers)
		{
			Container->EnableCollision(false);
		}
	}
}