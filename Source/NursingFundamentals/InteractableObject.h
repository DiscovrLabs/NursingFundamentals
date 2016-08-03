// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "InteractableObject.generated.h"

UINTERFACE(Blueprintable)
class NURSINGFUNDAMENTALS_API UInteractableObject : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IInteractableObject
{
	GENERATED_IINTERFACE_BODY()

public:

	virtual void ClickButton() = 0;
	virtual void SetHovered(bool bHovered) = 0;
};
