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
	Volume->InitBoxExtent(FVector(400.0f, 100.0f, 100.0f));
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



