// Fill out your copyright notice in the Description page of Project Settings.


#include "Fuse.h"

// Sets default values
AFuse::AFuse()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Signs = { "FilledCircle", "EmptyCircle", "FilledSquare", "EmptySquare" };

	RotationIndex = 0;
}

AFuse::AFuse(FString up, FString right, FString down, FString left)
{
	Signs = { up,right,down,left };
}

void AFuse::Rotate()
{
	RotationIndex = (RotationIndex + 1) % 4;

	// Calculate the new rotation angle
	float NewYaw = RotationIndex * 90.0f;

	// Update the actor's rotation
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw = NewYaw;
	SetActorRotation(NewRotation);

}

// Called when the game starts or when spawned
void AFuse::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFuse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

