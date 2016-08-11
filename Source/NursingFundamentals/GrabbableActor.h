// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GrabComponent.h"
#include "ScriptManager.h"
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

	//int32 GetCarryCount();

	virtual bool SetCarried(bool bIsCarried, UGrabComponent* CarryingHand, bool bLeftHand);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
		UStaticMeshComponent* ActorMesh;

	UFUNCTION(BlueprintImplementableEvent, Category = "Script")
		void TriggerInteraction();

	UFUNCTION(BlueprintCallable, Category = "Script")
		void DetachFromHand();

	int32 GetActorID();
	void SetCanCarry(bool A);
	void SetManager(AScriptManager* NewManager);
	void SetHighlighted();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		AScriptManager* Manager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 ActorID;

	UFUNCTION(BlueprintCallable, Category = "Script")
		void TellManager();

	UGrabComponent* AttachedHand;
	bool bCanCarry;
};
