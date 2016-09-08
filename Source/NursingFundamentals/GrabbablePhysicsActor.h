// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GrabbableActor.h"
#include "GrabbablePhysicsActor.generated.h"

/**
 * 
 */
UCLASS()
class NURSINGFUNDAMENTALS_API AGrabbablePhysicsActor : public AGrabbableActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	AGrabbablePhysicsActor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual bool SetCarried(bool bIsCarried, UGrabComponent* CarryingHand, bool bLeftHand) override;
	virtual void ResetActor();

	void AddVelocity(FVector Velocity);
	//void SetGravityScale();
	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	UProjectileMovementComponent* MovementComponent;
	*/
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawn")
		float KillZ;
	FTransform SpawnPos;
	float ResetTimer;

	FVector PreviousPos;
	FVector AvgDirection;
	float AvgSpeed;

	bool bFirstFrame;
	bool bCalcPhysics;
};
