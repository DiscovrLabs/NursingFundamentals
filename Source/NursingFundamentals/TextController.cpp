// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "TextController.h"



ATextController::ATextController()
{
	DisplayName = CurrentString = "";
	Name = "";
	StrIndex = 0;
	bCursorOn = false;
	bTypingName = true;
}

void ATextController::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(CursorTimer, this, &ATextController::NeutralCursor, 0.7f, true);
}

// Called every frame
void ATextController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorRotation(FRotationMatrix::MakeFromX(UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->GetCameraLocation() - GetActorLocation()).Rotator());
}


void ATextController::SetText(FString _Name, FString _Desc)
{
	UE_LOG(LogTemp, Warning, TEXT("Name: %s , Desc: %s"), *_Name, *_Desc);
	UpdateDesc("");
	CurrentString = "";
	StrIndex = 0;
	GetWorldTimerManager().ClearTimer(CursorTimer);

	if (_Name != "")
	{
		UpdateText("");
		Name = DisplayName = _Name;
		bTypingName = true;
	}
	Desc = DisplayDesc = _Desc;
	GetWorldTimerManager().SetTimer(CursorTimer, this, &ATextController::TypeText, 0.04f, true);
}

void ATextController::Reset()
{
	UpdateText("");
	CurrentString = "";
	Name = Desc = "";
	StrIndex = 0;
	GetWorldTimerManager().SetTimer(CursorTimer, this, &ATextController::NeutralCursor, 0.7f, true);
}

void ATextController::TypeText()
{
	if (bTypingName)
	{
		CurrentString = DisplayName.Left(StrIndex);
		UpdateText(CurrentString);
		StrIndex++;

		if (StrIndex > DisplayName.Len())
		{
			if (DisplayDesc == "")
			{
				bCursorOn = false;
				GetWorldTimerManager().SetTimer(CursorTimer, this, &ATextController::BlinkingCursor, 0.7f, true);
			}
			else
			{
				bTypingName = false;
				StrIndex = 0;
			}
		}
	}
	else
	{
		CurrentString = DisplayDesc.Left(StrIndex);
		UpdateDesc(CurrentString);
		StrIndex++;

		if (StrIndex > DisplayDesc.Len())
		{
			bCursorOn = false;
			GetWorldTimerManager().SetTimer(CursorTimer, this, &ATextController::BlinkingCursor, 0.7f, true);
		}
	}
}

void ATextController::NeutralCursor()
{
	if (bCursorOn)
	{
		UpdateText("");
		UpdateDesc("");
		bCursorOn = false;
	}
	else
	{
		UpdateText(L"█");
		bCursorOn = true;
	}
}

void ATextController::BlinkingCursor()
{
	if (bCursorOn)
	{
		CurrentString = CurrentString.LeftChop(2);
		(bTypingName) ? UpdateText(CurrentString) : UpdateDesc(CurrentString);
		bCursorOn = false;
	}
	else
	{
		CurrentString.Append(L" █");
		(bTypingName) ? UpdateText(CurrentString) : UpdateDesc(CurrentString);
		bCursorOn = true;
	}
}
