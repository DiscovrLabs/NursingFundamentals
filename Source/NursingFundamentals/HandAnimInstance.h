// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "HandAnimInstance.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class NURSINGFUNDAMENTALS_API UHandAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UHandAnimInstance();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PoseValues)
		bool bGrabbing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PoseValues)
		bool bPointing;
};
