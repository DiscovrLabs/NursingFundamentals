// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "RolodexMenu.h"

// Sets default values
ARolodexMenu::ARolodexMenu()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	SecondaryRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SecondaryRoot"));
	SecondaryRoot->SetupAttachment(Root);

	LerpAlpha = WidgetOffset = 0.0f;
	WidgetRotation = FVector::ZeroVector;
	TargetRotation = FQuat::Identity;
	bRotating = false;
}

// Called when the game starts or when spawned
void ARolodexMenu::BeginPlay()
{
	Super::BeginPlay();

	CurrentRotation = GetActorRotation().Quaternion();
}

// Called every frame
void ARolodexMenu::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bRotating)
	{
		LerpAlpha = FMath::Clamp(LerpAlpha + DeltaTime * 4.f, 0.f, 1.f);
		SecondaryRoot->SetWorldRotation(FQuat::Slerp(CurrentRotation, TargetRotation, LerpAlpha));

		if (LerpAlpha >= 1)
		{
			bRotating = false;
		}
	}
}

void ARolodexMenu::RotateMenu(bool bRotateDown)
{
	if (!bRotating)
	{
		LerpAlpha = 0;
		CurrentRotation = SecondaryRoot->GetComponentRotation().Quaternion();
		FQuat Temp = (bRotateDown) ? FQuat(CurrentRotation.GetRightVector(), FMath::DegreesToRadians(WidgetRotation.Y)) : FQuat(-CurrentRotation.GetRightVector(), FMath::DegreesToRadians(WidgetRotation.Y));
		TargetRotation = Temp * CurrentRotation;
		bRotating = true;
	}
	else
	{
		//Queue up more turns
	}
}

void ARolodexMenu::InitializeMenu(TArray<FString> Info)
{
	WidgetRotation = FVector(0, 360 / Info.Num(), 0);
	SpawnMenu(Info);
}

void ARolodexMenu::DestroyMenu()
{
	for (int i = 0; i < WidgetArray.Num(); i++)
	{
		WidgetArray[i]->Destroy();
	}
	Destroy();
}

void ARolodexMenu::SpawnMenu(TArray<FString> Info)
{
	UWorld* TempWorld = GetWorld();
	ALockedWidget* TempWidget;

	for (int i = 0; i < Info.Num(); i++)
	{
		TempWidget = TempWorld->SpawnActor<ALockedWidget>(WidgetBP, GetActorLocation() + GetActorRotation().Quaternion().GetForwardVector() * WidgetOffset, GetActorRotation());
		TempWidget->SetActorScale3D(GetActorScale3D());
		TempWidget->AttachToComponent(SecondaryRoot, FAttachmentTransformRules::KeepWorldTransform);
		TempWidget->SetParentActor(this);
		TempWidget->SetWidgetText(Info[i]);
		WidgetArray.Add(TempWidget);
		SecondaryRoot->AddLocalRotation(FQuat::MakeFromEuler(WidgetRotation));
	}
}
