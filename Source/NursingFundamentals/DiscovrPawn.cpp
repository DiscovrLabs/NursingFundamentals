// Fill out your copyright notice in the Description page of Project Settings.

#include "NursingFundamentals.h"
#include "HandAnimInstance.h"
#include "DiscovrPawn.h"


// Sets default values
ADiscovrPawn::ADiscovrPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	VROrigin = CreateDefaultSubobject<USceneComponent>(TEXT("VROrigin"));
	VROrigin->SetupAttachment(Root);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VROrigin);

	LeftHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("LeftHand"));
	LeftHand->SetupAttachment(VROrigin);

	RightHand = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("RightHand"));
	RightHand->SetupAttachment(VROrigin);

	LHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LHandMesh"));
	LHandMesh->SetupAttachment(LeftHand);

	RHandMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("RHandMesh"));
	RHandMesh->SetupAttachment(RightHand);

	RLaserOrigin = CreateDefaultSubobject<USceneComponent>(TEXT("RLaserOrigin"));
	RLaserOrigin->SetupAttachment(RHandMesh, FName(TEXT("FingerTip")));

	LeftPalm = CreateDefaultSubobject<UGrabComponent>(TEXT("LeftPalm"));
	LeftPalm->bLeftHand = true;
	LeftPalm->SetupAttachment(LHandMesh);

	RightPalm = CreateDefaultSubobject<UGrabComponent>(TEXT("RightPalm"));
	RightPalm->bLeftHand = true;
	RightPalm->SetupAttachment(RHandMesh);
}

// Called when the game starts or when spawned
void ADiscovrPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADiscovrPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADiscovrPawn::SetGrabbing(bool _bGrabbing, bool bLeftHand)
{
	
	UHandAnimInstance * Animation = Cast<UHandAnimInstance>((bLeftHand) ? LHandMesh->GetAnimInstance() : RHandMesh->GetAnimInstance());

	//No Anim Instance Acquired?
	if (!Animation) return;

	//Set Animblueprint data
	Animation->bGrabbing = _bGrabbing;
	
}