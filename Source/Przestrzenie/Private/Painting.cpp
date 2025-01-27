// Fill out your copyright notice in the Description page of Project Settings.


#include "Painting.h"

// Sets default values
APainting::APainting()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
    //MeshComponent->SetupAttachment(Root);
    UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube.Cube")).Object;

    // Set the component's mesh
    MeshComponent->SetStaticMesh(CubeMesh);
    MeshComponent->bCastDynamicShadow = true;
    MeshComponent->CastShadow = true;



}

// Called when the game starts or when spawned
void APainting::BeginPlay()
{
	Super::BeginPlay();

    Material = MeshComponent->GetMaterial(0); // Slot 0 of the material
    if (Material)
    {
        DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);

        // If it's not already a dynamic material, create one
        if (!DynamicMaterial)
        {
            DynamicMaterial = UMaterialInstanceDynamic::Create(Material, this);

            // Assign the dynamic material back to the mesh
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

