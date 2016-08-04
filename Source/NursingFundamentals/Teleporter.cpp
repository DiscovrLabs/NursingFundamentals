// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "TeleportManager.h"
#include "Teleporter.h"


// Sets default values
ATeleporter::ATeleporter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	RootComponent = SphereCollider;
	SphereCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	SphereCollider->SetSphereRadius(32);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	WidgetComponent->SetupAttachment(SphereCollider);

	GazeTimer = 0;
	bIsHovered = false;
	bEnabled = true;
}

// Called when the game starts or when spawned
void ATeleporter::BeginPlay()
{
	Super::BeginPlay();
	Player = Cast<ADiscovrPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	WidgetComponent->SetHiddenInGame(false);

	if (!bEnabled)
	{
		EnableTeleporter(false);
	}
}

// Called every frame
void ATeleporter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	if (bIsHovered)
	{
		GazeTimer += DeltaTime;
		if (GazeTimer >= 2.5f)
		{
			ClickButton();
		}
	}
}

// Called when clicked on by laser
void ATeleporter::ClickButton()
{
	FVector PlayerLoc = Player->GetActorLocation();
	Player->SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, PlayerLoc.Z));
	EnableTeleporter(false);
}

// Called when laser enters or exits hovering
void ATeleporter::SetHovered(bool bHovered)
{
	SetWidgetHovered(bHovered);
	if (bHovered)
	{
		bIsHovered = true;
	}
	else
	{
		bIsHovered = false;
		GazeTimer = 0;
	}
}

void ATeleporter::EnableTeleporter(bool Enable)
{
	if (Enable)
	{
		SphereCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		WidgetComponent->SetHiddenInGame(false);
	}
	else
	{
		SphereCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WidgetComponent->SetHiddenInGame(true);
		Cast<ATeleportManager>(TeleportManager)->SetDisabledTeleporter(this);
	}
}