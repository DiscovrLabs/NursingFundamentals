// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "LockedWidget.h"


// Sets default values
ALockedWidget::ALockedWidget()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ALockedWidget::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALockedWidget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorRotation(Parent->GetActorRotation());
}

void ALockedWidget::SetParentActor(AActor * Target)
{
	Parent = Target;
}
