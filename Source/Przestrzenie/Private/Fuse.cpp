// Fill out your copyright notice in the Description page of Project Settings.


#include "Fuse.h"

AFuse::AFuse()
{

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetupAttachment(Root);
	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cylinder.Cylinder")).Object;

	Cube->SetStaticMesh(CubeMesh);
	Cube->bCastDynamicShadow = true;
	Cube->CastShadow = true;
	Cube->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SignValues = { 1,2,3,4};
	RotationIndex = 0;

	RotationSpeed = 2.0f;
	IsRotating = false;
	RotationAlpha = 0.0f;
}

AFuse::AFuse(int up, int right, int down, int left)
{
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	//Cube->SetupAttachment(Root);
	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube.Cube")).Object;

	Cube->SetStaticMesh(CubeMesh);
	Cube->bCastDynamicShadow = true;
	Cube->CastShadow = true;

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotationIndex = 0;
	SignValues = {up, right, down, left};
}

void AFuse::Rotate()
{
	RotationIndex = (RotationIndex + 1) % 4;
	float NewRoll = RotationIndex * 90.0f;
	FRotator NewRotation = GetActorRotation();
	NewRotation.Roll = NewRoll;
	SetActorRotation(NewRotation);

	
	for (int32 i = 0; i < SignValues.Num(); i++)
	{
		int32 NewIndex = (i + RotationIndex) % SignValues.Num();
		CurrentRotationSigns[NewIndex] = SignValues[i];
	}

	OnRotate.Broadcast();

}

// Called when the game starts or when spawned
void AFuse::BeginPlay()
{
	Super::BeginPlay();
	
	OnClicked.AddDynamic(this, &AFuse::OnFuseClicked);

	TArray<UChildActorComponent*> ChildActorComponents;
	GetComponents<UChildActorComponent>(ChildActorComponents);

	/*
	for (UChildActorComponent* ChildActor : ChildActorComponents)
	{
		if (ASign* Sign = Cast<ASign>(ChildActor->GetChildActor()))
		{
			if (ChildActor->GetAttachParent() == Cube)
			{
				FString SignName = Sign->GetName();
				int32 Index = Sign->GetSignIndex();

				if (Signs.Num() <= Index)
				{
					Signs.SetNum(Index + 1);
				}

				Sign->SetSignVariant(SignValues[Index]-1);
				Sign->SetSignMaterial();
				Signs[Index] = Sign;

			}
		}
	}
	*/
	CurrentRotationSigns = SignValues;

	int randNum = (rand() % 4) + 1;

	for (int i = 0; i < randNum; ++i)
	{
		Rotate();
	}

	TargetRotation = GetActorRotation();
	StartRotation = GetActorRotation();
}

// Called every frame
void AFuse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsRotating)
	{
		RotationAlpha += DeltaTime * RotationSpeed;
		if (RotationAlpha >= 1.0f)
		{
			RotationAlpha = 1.0f;
			IsRotating = false;
			RotationIndex = (RotationIndex + 1) % 4;
			for (int32 i = 0; i < SignValues.Num(); i++)
			{
				int32 NewIndex = (i + RotationIndex) % SignValues.Num();
				CurrentRotationSigns[NewIndex] = SignValues[i];
			}

			OnRotate.Broadcast();
		}

		FRotator NewRotation = FRotator(StartRotation.Pitch, StartRotation.Yaw, FMath::Lerp(StartRotation.Roll, TargetRotation.Roll, RotationAlpha));
		SetActorRotation(NewRotation);
	}

}

void AFuse::OnFuseClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	if (TouchedActor == this)
	{
		if (!IsRotating)
		{
			StartRotation = FRotator(StartRotation.Pitch, StartRotation.Yaw, GetActorRotation().Roll);
			TargetRotation = StartRotation + FRotator(0.0f, 0.0f, 90.0f);
			RotationAlpha = 0.0f;
			IsRotating = true;

		}
	}
}