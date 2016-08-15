// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "WidgetContainer.h"


// Sets default values
AWidgetContainer::AWidgetContainer()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(Root);

}

// Called when the game starts or when spawned
void AWidgetContainer::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWidgetContainer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

