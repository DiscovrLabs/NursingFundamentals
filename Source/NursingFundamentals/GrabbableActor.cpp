// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "GrabbableActor.h"


// Sets default values
AGrabbableActor::AGrabbableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));
	RootComponent = ActorMesh;
}

// Called when the game starts or when spawned
void AGrabbableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGrabbableActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool AGrabbableActor::SetCarried(bool bIsCarried, UGrabComponent* CarryingHand, bool bLeftHand)
{
	if (bIsCarried)
	{
		//AudioComp->Play();
		CarryingHand->AttachObject(this, true);
	}
	else
	{
		CarryingHand->AttachObject(this, false);
	}
	return true;
}