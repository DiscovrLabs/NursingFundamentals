// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "AssessmentTrigger.h"


// Sets default values
AAssessmentTrigger::AAssessmentTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(Root);
	BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//BoxCollider->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);
	//BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(Root);
	WidgetComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bIsHovered = false;
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
	bIsHovered = bHovered;

	if (bHovered)
		WidgetComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	else
		WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAssessmentTrigger::EnableCollision(bool bEnable)
{
	if (bEnable)
	{
		BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		WidgetComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		BoxCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		WidgetComponent->SetVisibility(false);
		bIsHovered = false;
	}
}