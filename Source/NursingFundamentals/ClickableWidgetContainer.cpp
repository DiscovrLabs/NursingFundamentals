// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "ClickableWidgetContainer.h"


// Sets default values
AClickableWidgetContainer::AClickableWidgetContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(Root);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	BoxCollider->SetupAttachment(Root);

	Alpha = 0;
	bChangeDirection = bChangingSize = bClickedOn = false;
}

// Called when the game starts or when spawned
void AClickableWidgetContainer::BeginPlay()
{
	Super::BeginPlay();
	StartScale = GetActorScale();
	
}

// Called every frame
void AClickableWidgetContainer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bChangingSize)
	{
		//EndLocation = FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::X) * 30.f + StartLocation;
		EndLocation = FVector(30.f, LocalOffset.Y, LocalOffset.Z);
		if (bChangeDirection)
		{
			Alpha = FMath::Clamp(Alpha + DeltaTime * 4.f, 0.f, 1.f);
			SetActorRelativeLocation(FMath::Lerp(StartLocation, EndLocation, Alpha));
			if (Alpha >= 1)
				bChangingSize = false;
		}
		else
		{
			Alpha = FMath::Clamp(Alpha - DeltaTime * 4.f, 0.f, 1.f);
			SetActorRelativeLocation(FMath::Lerp(StartLocation, EndLocation, Alpha));
			if (Alpha <= 0)
				bChangingSize = false;
		}
	}
}

// Called when clicked on by laser
void AClickableWidgetContainer::ClickButton()
{
	//Manager->ConfirmSelection(ModuleBP);
	//Manager->DisableOtherContainers(this);
}

// Called when laser enters or exits hovering
void AClickableWidgetContainer::SetHovered(bool bHovered)
{
	if (!bClickedOn)
	{
		bChangeDirection = bHovered;
		bChangingSize = true;
		SetWidgetHovered(bHovered);
	}
}

void AClickableWidgetContainer::DisableContainer()
{
	bClickedOn = false;
	SetHovered(false);
	EnableCollision(true);
}

// Enable or disable collision
void AClickableWidgetContainer::EnableCollision(bool bEnable)
{
	if (bEnable)
	{
		BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
		BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Set start location
void AClickableWidgetContainer::SetStartLocation(FVector Start)
{
	StartLocation = Start;
}
