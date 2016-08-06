// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "AssessmentTrigger.h"


// Sets default values
AAssessmentTrigger::AAssessmentTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

	//BoxCollider->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);
	//BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(BoxCollider);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AAssessmentTrigger::BeginPlay()
{
	Super::BeginPlay();

	WidgetComponent->SetVisibility(false);
}

// Called every frame
void AAssessmentTrigger::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called when laser enters or exits hovering
void AAssessmentTrigger::SetHovered(bool bHovered)
{
	WidgetComponent->SetVisibility(bHovered);
}

void AAssessmentTrigger::EnableCollision(bool bEnable)
{
	if (bEnable)
	{
		WidgetComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}