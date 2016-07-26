// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "InteractionCollider.h"


// Sets default values
AInteractionCollider::AInteractionCollider()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	RootComponent = BoxCollider;

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
	UE_LOG(LogTemp, Warning, TEXT("Collided"));

	AGrabbableActor* TempActor = Cast<AGrabbableActor>(OtherActor);
	if (TempActor->GetActorID() == ColliderID)
	{
		TempActor->TriggerInteraction();
	}
}

void AInteractionCollider::OnEndOverlap(AActor* Actor, AActor * OtherActor)
{

}

