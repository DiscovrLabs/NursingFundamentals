// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GazeTrigger.generated.h"

UINTERFACE(Blueprintable)
class NURSINGFUNDAMENTALS_API UGazeTrigger : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IGazeTrigger
{
	GENERATED_IINTERFACE_BODY()

public:
	virtual void SetHovered(bool bHovered) = 0;
};
