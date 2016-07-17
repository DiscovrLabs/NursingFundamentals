// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "GrabComponent.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class NURSINGFUNDAMENTALS_API UGrabComponent : public USphereComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UGrabComponent();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void GrabItem();
	void DropItem();
	bool HasItem();
	void ForceItem(AActor* Item);
	void SetHolding(bool bHolding);
	AActor* GetItem();
	void AttachObject(AActor* Target, bool bConnect);

	bool bLeftHand;

protected:
	TArray<AActor*> HoldTargets;
	AActor* HeldItem;
	bool bHoldingItem;

	AActor* FindClosestToPalm();
	UFUNCTION()
		void OnBeginOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
		void OnEndOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
