// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GrabbableActor.h"
#include "ClickableActor.generated.h"

/**
 * 
 */
UCLASS()
class NURSINGFUNDAMENTALS_API AClickableActor : public AGrabbableActor
{
	GENERATED_BODY()

public:
	AClickableActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		USkeletalMesh* NewMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* BoxCollider;

	bool SetCarried(bool bIsCarried, UGrabComponent* CarryingHand, bool bLeftHand) override;

protected:
	bool bSwapped;
};
