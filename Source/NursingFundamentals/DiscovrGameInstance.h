// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "DiscovrGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class NURSINGFUNDAMENTALS_API UDiscovrGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UDiscovrGameInstance();
	bool bTutorial;
	
	
};
