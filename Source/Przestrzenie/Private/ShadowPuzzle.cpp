// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowPuzzle.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include <EnhancedInputComponent.h>
//#include "TP_PickUpComponent.h"

// Sets default values
AShadowPuzzle::AShadowPuzzle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Root);

    Mesh->bCastDynamicShadow = true;
    Mesh->CastShadow = true;
    
    // Create a CameraComponent	
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(Root);
    CameraComponent->SetRelativeLocationAndRotation(
        FVector(-38.f, -43.f, -10.f), 
        FRotator(0.0f, 35.0f, 0.0f)); // Position the camera
    
    SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
    SpotLight->SetupAttachment(Root);
    SpotLight->SetIntensity(5000.0f); // Default intensity
    SpotLight->SetLightColor(FLinearColor::White); // Default light color
    SpotLight->SetInnerConeAngle(6.0f); // Inner cone angle
    SpotLight->SetOuterConeAngle(9.0f); // Outer cone angle
    SpotLight->SetAttenuationRadius(1000.0f); // How far the light reaches
    SpotLight->SetRelativeLocation(FVector(-200.0f, 0.0f, 0.0f)); // Position it to the right of the actor

    Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
    Volume->SetupAttachment(Root);
    Volume->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
    Volume->SetCollisionProfileName(TEXT("OverlapAll"));
}

void AShadowPuzzle::PossesMe()
{
    // Get the player controller
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        PreviousPawn = PlayerController->GetPawn();
        // Possess this actor
        PlayerController->Possess(this);

        UE_LOG(LogTemp, Log, TEXT("Interact %s has been possessed by %s"), *GetName(), *PlayerController->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Interact No PlayerController found to possess %s"), *GetName());
    }
}

// Called when the game starts or when spawned
void AShadowPuzzle::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShadowPuzzle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShadowPuzzle::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // Set up action bindings
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        // Moving
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShadowPuzzle::Rotate);
        // Interact
        EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &AShadowPuzzle::Interact);
    }
}

void AShadowPuzzle::Rotate(const FInputActionValue& Value)
{
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        // UE_LOG(LogTemp, Log, TEXT("Rotate"));
        // Add rotation to the specific mesh component
        FRotator RotationDelta = FRotator::ZeroRotator;

        // Apply rotation based on input
        RotationDelta.Yaw = MovementVector.X;  // Rotate around the Z-axis (yaw)
        RotationDelta.Pitch = MovementVector.Y; // Rotate around the Y-axis (pitch)

        Mesh->AddLocalRotation(RotationDelta);
    }
}

void AShadowPuzzle::Interact(const FInputActionValue& Value)
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController && PreviousPawn)
    {
        // Possess this actor
        PlayerController->Possess(PreviousPawn);
        UE_LOG(LogTemp, Log, TEXT("Interact %s has been possessed by %s"), *PreviousPawn->GetName(), *PlayerController->GetName());
    }
}

