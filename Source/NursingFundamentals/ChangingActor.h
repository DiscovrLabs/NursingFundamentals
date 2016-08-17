// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GrabbablePhysicsActor.h"
#include "ChangingActor.generated.h"

/**
 * 
 */
UCLASS()
class NURSINGFUNDAMENTALS_API AChangingActor : public AGrabbablePhysicsActor
{
	GENERATED_BODY()

public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool SetCarried(bool bIsCarried, UGrabComponent* CarryingHand, bool bLeftHand) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "Tutorial")
		void TellManager(bool bDropped);

protected:
	UStaticMesh* StartMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMesh* GrabbedMesh;
};
