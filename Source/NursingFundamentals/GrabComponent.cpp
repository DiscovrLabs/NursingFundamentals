// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "GrabbableActor.h"
#include "GrabComponent.h"

UGrabComponent::UGrabComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	bAutoActivate = true;
	this->OnComponentBeginOverlap.AddDynamic(this, &UGrabComponent::OnBeginOverlap);
	this->OnComponentEndOverlap.AddDynamic(this, &UGrabComponent::OnEndOverlap);
}

void UGrabComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UGrabComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (HoldTargets.Num() > 0 && !bHoldingItem)
	{
		AActor* TempActor = FindClosestToPalm();
		if (HighlightedItem != TempActor)
		{
			if (HighlightedItem)
			{
				Cast<AGrabbableActor>(HighlightedItem)->SetHighlighted(false);
			}
			Cast<AGrabbableActor>(TempActor)->SetHighlighted(true);
			HighlightedItem = TempActor;
		}
	}
}

void UGrabComponent::GrabItem()
{
	if (HoldTargets.Num() > 0)
	{
		HeldItem = HighlightedItem;
		bHoldingItem = Cast<AGrabbableActor>(HeldItem)->SetCarried(true, this, bLeftHand);

		if (bHoldingItem)
		{
			UGameplayStatics::GetPlayerController(GetWorld(), 0)->ClientPlayForceFeedback(HapticEffect, false, FName("Grab"));
			Cast<AGrabbableActor>(HighlightedItem)->SetHighlighted(false);
			HighlightedItem = NULL;
		}
	}
	else
	{
		bHoldingItem = false;
	}
}

void UGrabComponent::DropItem()
{
	if (bHoldingItem)
	{
		Cast<AGrabbableActor>(HeldItem)->SetCarried(false, this, bLeftHand);
		bHoldingItem = false;
	}
}

bool UGrabComponent::HasItem()
{
	return bHoldingItem;
}

void UGrabComponent::SetHolding(bool bHolding)
{
	bHoldingItem = bHolding;
}

void UGrabComponent::ForceItem(AActor * Item)
{
	HeldItem = Item;
}

AActor* UGrabComponent::GetItem()
{
	if (bHoldingItem)
	{
		return HeldItem;
	}
	else return NULL;
}

void UGrabComponent::AttachObject(AActor* Target, bool bConnect)
{
	if (bConnect)
	{
		Target->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
	}
	else
	{
		if (this->GetAttachChildren().Contains(Target->GetRootComponent()))
		{
			Target->DetachRootComponentFromParent();
		}
	}
}

AActor* UGrabComponent::FindClosestToPalm()
{
	AActor* TempActor = HoldTargets[0];
	float Distance = 50000;
	for (int i = 0; i < HoldTargets.Num(); i++)
	{
		float TempDist = (this->GetComponentLocation() - HoldTargets[i]->GetActorLocation()).SizeSquared();
		if (TempDist < Distance)
		{
			TempActor = HoldTargets[i];
			Distance = TempDist;
		}
	}
	return TempActor;
}

void UGrabComponent::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA<AGrabbableActor>() && !bHoldingItem)
	{
		HoldTargets.Add(OtherActor);
	}
}

void UGrabComponent::OnEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (HoldTargets.Contains(OtherActor))
	{
		if (HighlightedItem == OtherActor)
		{
			Cast<AGrabbableActor>(OtherActor)->SetHighlighted(false);
			HighlightedItem = NULL;
		}
		HoldTargets.Remove(OtherActor);
	}
}