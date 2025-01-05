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

	Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
	Volume->SetupAttachment(Root);
	Volume->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	Volume->SetCollisionProfileName(TEXT("OverlapAll"));
}

void AFuseboxPuzzle::PossesMe()
{
	// Get the player controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PreviousPawn = PlayerController->GetPawn();
		// Possess this actor
		PlayerController->Possess(this);

		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
	}
}

void AFuseboxPuzzle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AFuseboxPuzzle::Interact);
	}
}

void AFuseboxPuzzle::Interact(const FInputActionValue& Value)
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && PreviousPawn)
	{
		PlayerController->bShowMouseCursor = false;
		PlayerController->bEnableClickEvents = false;
		// Possess this actor
		PlayerController->Possess(PreviousPawn);
	}
}

void AFuseboxPuzzle::CheckSolution()
{
}

// Called when the game starts or when spawned
void AFuseboxPuzzle::BeginPlay()
{
	Super::BeginPlay();
	//SpawnFuses();

	TArray<UChildActorComponent*> ChildActorComponents;
	GetComponents<UChildActorComponent>(ChildActorComponents);


	for (UChildActorComponent* ChildActor : ChildActorComponents)
	{
		if (AFuse* Fuse = Cast<AFuse>(ChildActor->GetChildActor()))
		{
			if (ChildActor->GetAttachParent() == Cube)
			{
				FString FuseName = Fuse->GetName();
				int32 Index = Fuse->GetFuseIndex();
				
				if (Fuses.Num() <= Index)
				{
					Fuses.SetNum(Index + 1);
				}
				Fuses[Index] = Fuse;

			}
		}
	}
	
}

// Called every frame
void AFuseboxPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFuseboxPuzzle::SpawnFuses()
{
	FVector CubeLocation = GetActorLocation();
	FVector FrontFaceOffset = FVector(5.0f, 0.0f, 0.0f);

	FVector StartPosition = CubeLocation + FrontFaceOffset + FVector(0.0f, -FuseSpacingHorizontal, FuseSpacingVertical);

	for (int Row = 0; Row < 3; ++Row)
	{
		for (int Column = 0; Column < 2; ++Column)
		{
			FVector FusePosition = StartPosition;
			FusePosition.Y += Column * FuseSpacingHorizontal;
			FusePosition.Z -= Row * FuseSpacingVertical;

			FRotator FuseRotation = FRotator(0.0f, 0.0f, 0.0f);

			AFuse* NewFuse = GetWorld()->SpawnActor<AFuse>(AFuse::StaticClass(), FusePosition, FuseRotation);
			if (NewFuse)
			{
				Fuses.Add(NewFuse);
			}
		}
	}
}
