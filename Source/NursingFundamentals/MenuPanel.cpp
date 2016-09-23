// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "DiscovrPawn.h"
#include "TutorialManager.h"
#include "MenuPanel.h"


// Sets default values
AMenuPanel::AMenuPanel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MainClickableContainersLocations.Add(FVector2D(0, 14.5));
	MainClickableContainersLocations.Add(FVector2D(9, 0));
	MainClickableContainersLocations.Add(FVector2D(-9, 0));
	MainContainerMode = -1;
	HierarchyLevel = -1;

	SecClickableContainersLocations.Add(FVector2D(-8.0, 8.0));
	SecClickableContainersLocations.Add(FVector2D(8.0, 8.0));
	SecClickableContainersLocations.Add(FVector2D(-8.0, -8.0));
	SecClickableContainersLocations.Add(FVector2D(8.0, -8.0));
	SecContainerMode = 0;

	bTutorial = false;
}

// Called when the game starts or when spawned
void AMenuPanel::BeginPlay()
{
	Super::BeginPlay();

	TArray<AClickableWidgetContainer*> TempArray;
	for (int i = 0; i < MainClickableContainersLocations.Num(); i++)
	{
		TempArray.Add(GetWorld()->SpawnActor<AClickableWidgetContainer>(ClickableContainerBP));
		TempArray[i]->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, NAME_None);
		TempArray[i]->SetActorRotation(GetActorRotation());
		TempArray[i]->AddActorLocalOffset(FVector(0.f, MainClickableContainersLocations[i].X, MainClickableContainersLocations[i].Y));
		MainClickableContainers.Add(TempArray[i]);
		MainClickableContainers[i]->LocalOffset = FVector(0.f, MainClickableContainersLocations[i].X, MainClickableContainersLocations[i].Y);
		MainClickableContainers[i]->SetStartLocation(MainClickableContainers[i]->LocalOffset);
		MainClickableContainers[i]->ContainerNum = i + 1;
		MainClickableContainers[i]->ParentPanel = this;
	}

	TempArray.Empty();
	for (int i = 0; i < SecClickableContainersLocations.Num(); i++)
	{
		TempArray.Add(GetWorld()->SpawnActor<AClickableWidgetContainer>(ClickableContainerBP));
		TempArray[i]->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale, NAME_None);
		TempArray[i]->SetActorRotation(GetActorRotation());
		TempArray[i]->AddActorLocalOffset(FVector(0.f, SecClickableContainersLocations[i].X, SecClickableContainersLocations[i].Y));
		SecClickableContainers.Add(TempArray[i]);
		SecClickableContainers[i]->LocalOffset = FVector(0.f, SecClickableContainersLocations[i].X, SecClickableContainersLocations[i].Y);
		SecClickableContainers[i]->SetStartLocation(SecClickableContainers[i]->LocalOffset);
		SecClickableContainers[i]->ContainerNum = i + 4;
		SecClickableContainers[i]->ParentPanel = this;
	}
	SetupClickableWidgets(MainImages, MainNames, SecNames);

	this->AttachToComponent(Cast<ADiscovrPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0))->GetHandMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, "ThumbSocket");
	EnableUISet(false, 0);
	EnableUISet(false, 1);
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
		if (bTutorial)
		{
			Cast<ATutorialManager>(TutorialManager)->ButtonClicked(0);
			UE_LOG(LogTemp, Warning, TEXT("Charmander"));
		}
		return false;
	}
	// if menu is off or player is in the 2nd level of the menu, turn on the main level of the menu. else if player is in the 3rd level of the menu send them back to the 2nd
	if (HierarchyLevel == -1 || HierarchyLevel == 1)
	{
		EnableMode(0);
		if (bTutorial)
		{
			Cast<ATutorialManager>(TutorialManager)->ButtonClicked(0);
			UE_LOG(LogTemp, Warning, TEXT("Squirtle"));
		}
	}
	else if (HierarchyLevel == 2)
	{
		EnableMode(MainContainerMode);
	}
	return true;
}

void AMenuPanel::EnableUISet(bool bEnable, int32 Set)
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
		case 2:
			if (RolodexMenu)
			{
				RolodexMenu->DestroyMenu();
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
		if(bTutorial)
			Cast<ATutorialManager>(TutorialManager)->ButtonClicked(ContainerNum);
	}
}

void AMenuPanel::EnableMode(int32 Mode)
{
	TArray<TArray<FString>> TempArray;
	TempArray.Add(TextArray1);
	TempArray.Add(TextArray2);
	TempArray.Add(TextArray3);
	TempArray.Add(TextArray4);
	switch (Mode)
	{
	case -1: // Not Visible
		EnableUISet(false, 0);
		MainContainerMode = -1;
		HierarchyLevel = -1;
		//UE_LOG(LogTemp, Warning, TEXT("Case: -1"));
		break;
	case 0: // Not Selected
		EnableUISet(true, 0);
		if(SecContainerMode != -1)
			EnableUISet(false, 1);
		MainContainerMode = 0;
		HierarchyLevel = 0;
		Manager->EnableAssessments(false);
		//UE_LOG(LogTemp, Warning, TEXT("Case: 0"));
		break;
	case 1: // Communication
		EnableUISet(false, 0);
		EnableUISet(false, 2);
		EnableUISet(true, 1);
		MainContainerMode = 1;
		HierarchyLevel = 1;
		//UE_LOG(LogTemp, Warning, TEXT("Case: 1"));
		break;
	case 2: // Assessment
		EnableUISet(false, 0);
		Manager->EnableAssessments(true);
		MainContainerMode = 2;
		HierarchyLevel = 1;
		//UE_LOG(LogTemp, Warning, TEXT("Case: 2"));
		break;
	case 3: // Intervention
		//MainContainerMode = 3;
		//HierarchyLevel = 1;
		//UE_LOG(LogTemp, Warning, TEXT("Case: 3"));
		break;
	case 4:
	case 5:
	case 6:
	case 7:
		RolodexMenu = GetWorld()->SpawnActor<ARolodexMenu>(RolodexMenuBP);
		RolodexMenu->SetActorLocation(GetActorLocation() + FVector(0, 0, 20.f));
		RolodexMenu->SetActorRotation(FRotationMatrix::MakeFromX(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation() - RolodexMenu->GetActorLocation()).Rotator());
		RolodexMenu->SetActorScale3D(FVector(0.04f));
		//RolodexMenu->SetActorRotation(RolodexMenu->GetActorRotation() + FRotator(0,180.f,0));
		//RolodexMenu->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		//RolodexMenu->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		RolodexMenu->InitializeMenu(TempArray[Mode - 4]);
		EnableUISet(false, 1);
		SecContainerMode = Mode;
		HierarchyLevel = 2;
		//UE_LOG(LogTemp, Warning, TEXT("Case: 4+"));
		break;
	default:
		break;
	}
}

void AMenuPanel::ShowHealthRecord()
{
	if(bTutorial)
		Cast<ATutorialManager>(TutorialManager)->ButtonClicked(99);
}

void AMenuPanel::TurnRolodex(bool bRotateDown)
{
	if (RolodexMenu)
	{
		RolodexMenu->RotateMenu(bRotateDown);
	}
}

void AMenuPanel::EnableContianer(int32 ContainerNum, bool bEnable)
{
	MainClickableContainers[ContainerNum]->EnableCollision(bEnable);
	//UE_LOG(LogTemp, Warning, TEXT("Bool = %d & Container = %d"), bEnable, ContainerNum);
}

void AMenuPanel::SetTutorial(bool bEnable)
{
	bTutorial = bEnable;
}