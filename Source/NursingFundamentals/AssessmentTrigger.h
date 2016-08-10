// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GazeTrigger.h"
#include "Components/WidgetComponent.h"
#include "AssessmentTrigger.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API AAssessmentTrigger : public AActor, public IGazeTrigger
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAssessmentTrigger();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	virtual void SetHovered(bool bHovered) override;

	void EnableCollision(bool bEnable);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Root")
		USceneComponent* Root;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
		UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		UWidgetComponent* WidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lighting")
		UPointLightComponent* GlowLight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Root")
		bool bIsHovered;
};
