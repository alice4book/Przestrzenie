// Fill out your copyright notice in the Description page of Project Settings.


#include "Sign.h"

// Sets default values
ASign::ASign()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	//Cube->SetupAttachment(Root);
	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube.Cube")).Object;

	// Set the component's mesh
	Cube->SetStaticMesh(CubeMesh);
	Cube->bCastDynamicShadow = true;
	Cube->CastShadow = true;
}

void ASign::SetSignMaterial()
{
	Cube->SetMaterial(0, MaterialVariants[SignVariant]);
}

// Called when the game starts or when spawned
void ASign::BeginPlay()
{
	Super::BeginPlay();
	
	SetSignMaterial();
}

// Called every frame
void ASign::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

