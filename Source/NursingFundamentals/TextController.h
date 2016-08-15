// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WidgetContainer.h"
#include "TextController.generated.h"

/**
 * 
 */
UCLASS()
class NURSINGFUNDAMENTALS_API ATextController : public AWidgetContainer
{
	GENERATED_BODY()

public:
	ATextController();
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	void SetText(FString Name = "", FString _Desc = "");
	void Reset();

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "Text")
		void UpdateText(const FString &_Text);

	UFUNCTION(BlueprintImplementableEvent, Category = "Text")
		void UpdateDesc(const FString &_Text);

	void TypeText();
	void NeutralCursor();
	void BlinkingCursor();

	FTimerHandle CursorTimer;
	FString DisplayName;
	FString DisplayDesc;
	FString CurrentString;

	FString Name;
	FString Desc;
	int32 StrIndex;
	bool bCursorOn;
	bool bTypingName;
	
};
