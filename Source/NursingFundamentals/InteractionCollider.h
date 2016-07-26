// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GrabbableActor.h"
#include "InteractionCollider.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API AInteractionCollider : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractionCollider();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* BoxCollider;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Data")
		int32 ColliderID;

	UFUNCTION()
		void OnBeginOverlap(AActor* Actor, AActor * OtherActor);
	UFUNCTION()
		void OnEndOverlap(AActor* Actor, AActor * OtherActor);
};
