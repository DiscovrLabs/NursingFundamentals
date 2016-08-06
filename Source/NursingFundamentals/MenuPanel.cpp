// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "DiscovrPawn.h"
#include "MenuPanel.h"


// Sets default values
AMenuPanel::AMenuPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ClickableContainersLocations.Add(FVector2D(0, 7.5));
	ClickableContainersLocations.Add(FVector2D(-4.5, 0));
	ClickableContainersLocations.Add(FVector2D(4.5, 0));

	CurrentMode = 9;
}

// Called when the game starts or when spawned
void AMenuPanel::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> TempArray;
	for (int i = 0; i < ClickableContainersLocations.Num(); i++)
	{
		TempArray.Add(GetWorld()->SpawnActor(ClickaleContainerBP));
		TempArray[i]->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, NAME_None);
		TempArray[i]->SetActorRotation(GetActorRotation());
		TempArray[i]->AddActorLocalOffset(FVector(0.f, ClickableContainersLocations[i].X, ClickableContainersLocations[i].Y));
		ClickableContainers.Add(Cast<AClickableWidgetContainer>(TempArray[i]));
		ClickableContainers[i]->LocalOffset = FVector(0.f, ClickableContainersLocations[i].X, ClickableContainersLocations[i].Y);
		ClickableContainers[i]->SetStartLocation(ClickableContainers[i]->LocalOffset);
		ClickableContainers[i]->ContainerNum = i;
		ClickableContainers[i]->ParentPanel = this;
	}
	SetupClickableWidgets(ButtonImages);
	this->AttachToComponent(Cast<ADiscovrPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->GetHandMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "ThumbSocket");
	EnableClickableContainers(false);
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
			Container->SetActorHiddenInGame(false);
			Container->EnableCollision(true);
		}
	}
	else
	{
		for (AClickableWidgetContainer* Container : ClickableContainers)
		{
			Container->SetActorHiddenInGame(true);
			Container->EnableCollision(false);
		}
	}
}

void AMenuPanel::ContainerClicked(int32 ContainerNum)
{
	if (Manager)
	{
		if (ContainerNum == CurrentMode)
		{
			EnableMode(false, ContainerNum);
		}
		else
		{
			EnableMode(true, ContainerNum);
		}
	}
}

void AMenuPanel::EnableMode(bool bEnable, int32 Mode)
{
	switch (Mode)
	{
	case 0:
		break;
	case 1:
		Manager->EnableAssessments(true);
		break;
	case 2:
		break;
	default:
		break;
	}
}