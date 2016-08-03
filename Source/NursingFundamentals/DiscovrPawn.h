// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "Runtime/HeadMountedDisplay/Public/MotionControllerComponent.h"
#include "GrabComponent.h"
#include "DiscovrPawn.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API ADiscovrPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ADiscovrPawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetGrabbing(bool _bGrabbing, bool bLeftHand);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Laser")
		USceneComponent* RLaserOrigin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotionController")
		UMotionControllerComponent* LeftHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MotionController")
		UMotionControllerComponent* RightHand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grabbing")
		UGrabComponent* LeftPalm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grabbing")
		UGrabComponent* RightPalm;
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Root")
		USceneComponent* VROrigin;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
		UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		USkeletalMeshComponent* LHandMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		USkeletalMeshComponent* RHandMesh;
};
