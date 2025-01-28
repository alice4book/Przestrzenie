// Fill out your copyright notice in the Description page of Project Settings.


#include "Painting.h"

// Sets default values
APainting::APainting()
{

	PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
    //MeshComponent->SetupAttachment(Root);
    UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube.Cube")).Object;

    MeshComponent->SetStaticMesh(CubeMesh);
    MeshComponent->bCastDynamicShadow = true;
    MeshComponent->CastShadow = true;



}

void APainting::BeginPlay()
{
	Super::BeginPlay();

    Material = MeshComponent->GetMaterial(0); 
    if (Material)
    {
        DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);

        if (!DynamicMaterial)
        {
            DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

            MeshComponent->SetMaterial(0, DynamicMaterial);
        }

    }

    ChangeMaterialParameters(true);
	
}

// Called every frame
void APainting::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FuseboxPuzzle->isSolved && isMoving)
	{
		isMoving = false;
        ChangeMaterialParameters(false);
	}
}


void APainting::ChangeMaterialParameters(bool moving)
{
    if (DynamicMaterial)
    {
        if(moving)
        {
            DynamicMaterial->SetScalarParameterValue(TEXT("EyeLineSpeed"), 1.0f);
            DynamicMaterial->SetScalarParameterValue(TEXT("blink speed"), 1.0f);
            DynamicMaterial->SetScalarParameterValue(TEXT("ColourSpeed"), 0.4f);
            DynamicMaterial->SetScalarParameterValue(TEXT("pupil speed"), 0.05f);
            DynamicMaterial->SetScalarParameterValue(TEXT("rotation speed"), 0.001f);
        }
        else
        {
            DynamicMaterial->SetScalarParameterValue(TEXT("EyeLineSpeed"), 0.0f);
            DynamicMaterial->SetScalarParameterValue(TEXT("blink speed"), 0.0f);
            DynamicMaterial->SetScalarParameterValue(TEXT("ColourSpeed"), 0.0f);
            DynamicMaterial->SetScalarParameterValue(TEXT("pupil speed"), 0.0f);
            DynamicMaterial->SetScalarParameterValue(TEXT("rotation speed"), 0.0f);
        }

    }
}

