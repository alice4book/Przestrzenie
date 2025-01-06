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
	SignValues = { 1,2,3,4};
	//isChecked = {false,false,false,false};
	RotationIndex = 0;
}

AFuse::AFuse(int up, int right, int down, int left)
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
	SignValues = {up, right, down, left};
	//isChecked = { false,false,false,false };
}

void AFuse::Rotate()
{
	RotationIndex = (RotationIndex + 1) % 4;
	float NewRoll = RotationIndex * 90.0f;
	FRotator NewRotation = GetActorRotation();
	NewRotation.Roll = NewRoll;
	SetActorRotation(NewRotation);

	
	for (int32 i = 0; i < Signs.Num(); i++)
	{
		int32 NewIndex = (i + RotationIndex) % Signs.Num();
		CurrentRotationSigns[NewIndex] = Signs[i];
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

				//UE_LOG(LogTemp, Warning,TEXT("Index: %d"), SignValues[Index]-1);
				Sign->SetSignVariant(SignValues[Index]-1);
				Sign->SetSignMaterial();
				Signs[Index] = Sign;

			}
		}
	}

	CurrentRotationSigns = Signs;
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