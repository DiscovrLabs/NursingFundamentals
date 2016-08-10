// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "AssessmentTrigger.h"
#include "Manager.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API AManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void EnableAssessments(bool bEnable);

protected:
	/**************************************************************************
	* ASSESSMENT MENU
	**************************************************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TArray<AAssessmentTrigger*> AssessmentTriggers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TArray<FString> AssessmentInfo;

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
		void SetupAssessmentTriggers(const TArray<FString> &_Info);
};
