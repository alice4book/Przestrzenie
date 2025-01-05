// Fill out your copyright notice in the Description page of Project Settings.


#include "Fuse.h"

// Sets default values
AFuse::AFuse()
{
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	//Cube->SetupAttachment(Root);
	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube.Cube")).Object;

	// Set the component's mesh
	Cube->SetStaticMesh(CubeMesh);
	Cube->bCastDynamicShadow = true;
	Cube->CastShadow = true;
	Cube->SetRelativeScale3D(FVector(0.2f, 0.2f, 0.2f));

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Signs = { "A","B","C","D"};

	RotationIndex = 0;
}

AFuse::AFuse(FString up, FString right, FString down, FString left)
{
	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	//Cube->SetupAttachment(Root);
	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube.Cube")).Object;

	// Set the component's mesh
	Cube->SetStaticMesh(CubeMesh);
	Cube->bCastDynamicShadow = true;
	Cube->CastShadow = true;


	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RotationIndex = 0;
	Signs = { up,right,down,left };
}

void AFuse::Rotate()
{
	RotationIndex = (RotationIndex + 1) % 4;

	// Calculate the new rotation angle
	float NewRoll = RotationIndex * 90.0f;

	// Update the actor's rotation
	FRotator NewRotation = GetActorRotation();
	NewRotation.Roll = NewRoll;
	SetActorRotation(NewRotation);

}

// Called when the game starts or when spawned
void AFuse::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind the OnClicked event
	OnClicked.AddDynamic(this, &AFuse::OnFuseClicked);
}

// Called every frame
void AFuse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFuse::OnFuseClicked(AActor* TouchedActor, FKey ButtonPressed)
{
	if (TouchedActor == this)
	{
		Rotate();
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("Fuse clicked and rotated!"));
	}
}