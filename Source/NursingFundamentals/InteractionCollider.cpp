// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "InteractionCollider.h"


// Sets default values
AInteractionCollider::AInteractionCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->OnActorBeginOverlap.AddDynamic(this, &AInteractionCollider::OnBeginOverlap);
	this->OnActorBeginOverlap.AddDynamic(this, &AInteractionCollider::OnEndOverlap);
}

// Called when the game starts or when spawned
void AInteractionCollider::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractionCollider::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AInteractionCollider::OnBeginOverlap(AActor* Actor, AActor * OtherActor)
{
	FName ObjectID = OtherActor->Tags[0];
}

void AInteractionCollider::OnEndOverlap(AActor* Actor, AActor * OtherActor)
{

}

