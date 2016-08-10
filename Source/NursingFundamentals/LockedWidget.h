// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "LockedWidget.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API ALockedWidget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALockedWidget();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SetParentActor(AActor* Target);

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
		void SetWidgetText(const FString &_Info);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		UWidgetComponent* WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
		USceneComponent* Root;
	
	AActor* Parent;
};
