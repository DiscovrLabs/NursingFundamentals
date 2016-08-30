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
	ActorID = 99;

	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->AttachTo(RootComponent);

	bCanCarry = false;
}

// Called when the game starts or when spawned
void AGrabbableActor::BeginPlay()
{
	Super::BeginPlay();

	if (GrabSound)
	{
		AudioComp->SetSound(GrabSound);
	}

	ActorMesh->CreateDynamicMaterialInstance(0);
	ActorMesh->SetVectorParameterValueOnMaterials("Highlight", FVector::ZeroVector);
	/*
	TArray<AActor*> TempArray;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AScriptManager::StaticClass(), TempArray);
	Manager = Cast<AScriptManager>(TempArray[0]);
	*/
}

// Called every frame
void AGrabbableActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

bool AGrabbableActor::SetCarried(bool bIsCarried, UGrabComponent* CarryingHand, bool bLeftHand)
{
	if (bCanCarry)
	{
		if (bIsCarried)
		{
			AudioComp->Play();
			CarryingHand->AttachObject(this, true);
			AttachedHand = CarryingHand;
			UE_LOG(LogTemp, Warning, TEXT("Carried Object"));
		}
		else
		{
			CarryingHand->AttachObject(this, false);
			AttachedHand = NULL;
		}
		return true;
	}
	else
	{
		return false;
	}

}

void AGrabbableActor::DetachFromHand()
{
	if (AttachedHand)
	{
		AttachedHand->AttachObject(this, false);
		AttachedHand = NULL;
	}
}

int32 AGrabbableActor::GetActorID()
{
	return ActorID;
}

void AGrabbableActor::SetCanCarry(bool A)
{
	bCanCarry = A;
}

void AGrabbableActor::SetManager(AScriptManager* NewManager)
{
	Manager = NewManager;
}

void AGrabbableActor::TellManager()
{
	Manager->GamestateIncrement();
	if (AttachedHand)
	{
		AttachedHand->SetHolding(false);
	}
	DetachFromHand();
}

void AGrabbableActor::SetHighlighted(bool bHighlighted)
{
	if (bCanCarry)
	{
		if (bHighlighted)
		{
			ActorMesh->SetVectorParameterValueOnMaterials("Highlight", FVector(1, 0.892, 0.12));
		}
		else
		{
			ActorMesh->SetVectorParameterValueOnMaterials("Highlight", FVector::ZeroVector);
		}
	}
	else
	{
		ActorMesh->SetVectorParameterValueOnMaterials("Highlight", FVector::ZeroVector);
	}
}

bool AGrabbableActor::GetCarried()
{
	if (AttachedHand)
	{
		return true;
	}

	return false;
}
