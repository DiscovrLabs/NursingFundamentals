// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "ClickableActor.h"

AClickableActor::AClickableActor()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(Mesh);
}

void AClickableActor::BeginPlay()
{
	Super::BeginPlay();
	Mesh->CreateDynamicMaterialInstance(2);
	Mesh->SetVectorParameterValueOnMaterials("Highlight", FVector::ZeroVector);
}

bool AClickableActor::SetCarried(bool bIsCarried, UGrabComponent* CarryingHand, bool bLeftHand)
{
	if (bIsCarried && !bSwapped)
	{
		SetHighlighted(false);
		Mesh->OverrideMaterials.Empty();
		Mesh->SetSkeletalMesh(NewMesh, false);
		bSwapped = true;
		Manager->GamestateIncrement();
	}
	return false;
}

void AClickableActor::SetHighlighted(bool bHighlighted)
{
	if (!bSwapped)
	{
		if (bHighlighted)
		{
			//Mesh->SetVectorParameterValueOnMaterials("Highlight", FVector(1, 0.892, 0.12));
			UMaterialInstanceDynamic* temp = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(2));
			temp->SetVectorParameterValue("Highlight", FVector(1, 0.892, 0.12));
		}
		else
		{
			//Mesh->SetVectorParameterValueOnMaterials("Highlight", FVector::ZeroVector);
			UMaterialInstanceDynamic* temp = Cast<UMaterialInstanceDynamic>(Mesh->GetMaterial(2));
			temp->SetVectorParameterValue("Highlight", FVector::ZeroVector);
		}
	}
}
