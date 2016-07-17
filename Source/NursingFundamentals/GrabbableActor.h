// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GrabComponent.h"
#include "GrabbableActor.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API AGrabbableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabbableActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	int32 GetCarryCount();

	virtual bool SetCarried(bool bIsCarried, UGrabComponent* CarryingHand, bool bLeftHand);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* ActorMesh;
};
