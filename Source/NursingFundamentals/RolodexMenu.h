// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LockedWidget.h"
#include "RolodexMenu.generated.h"

UCLASS()
class NURSINGFUNDAMENTALS_API ARolodexMenu : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARolodexMenu();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Rotation")
		void RotateMenu(bool bRotateDown);

	void InitializeMenu(TArray<FString> Info);
	void DestroyMenu();
	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
		USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Root")
		USceneComponent* SecondaryRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		TSubclassOf<ALockedWidget> WidgetBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
		float WidgetOffset;

	void SpawnMenu(TArray<FString> Info);

	TArray<ALockedWidget*> WidgetArray;
	FVector WidgetRotation;
	FQuat CurrentRotation;
	FQuat TargetRotation;

	float LerpAlpha;
	bool bRotating;
};
