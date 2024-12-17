// Fill out your copyright notice in the Description page of Project Settings.


#include "FuseboxPuzzle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include <EnhancedInputComponent.h>

// Sets default values
AFuseboxPuzzle::AFuseboxPuzzle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	Cube->SetupAttachment(Root);
	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube.Cube")).Object;

	// Set the component's mesh
	Cube->SetStaticMesh(CubeMesh);
	Cube->bCastDynamicShadow = true;
	Cube->CastShadow = true;

	// Create a CameraComponent	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(Root);
	CameraComponent->SetRelativeLocationAndRotation(
		FVector(-250.f, -0.f, -0.f),
		FRotator(0.0f, 0.0f, 0.0f)); // Position the camera
}

// Called when the game starts or when spawned
void AFuseboxPuzzle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFuseboxPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



