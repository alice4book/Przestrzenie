// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowPuzzle.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
//#include "TP_PickUpComponent.h"

// Sets default values
AShadowPuzzle::AShadowPuzzle()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
    SpotLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("SpotLight"));
    SpotLight->SetupAttachment(RootComponent);

    SpotLight->SetIntensity(5000.0f); // Default intensity
    SpotLight->SetLightColor(FLinearColor::White); // Default light color
    SpotLight->SetInnerConeAngle(6.0f); // Inner cone angle
    SpotLight->SetOuterConeAngle(9.0f); // Outer cone angle
    SpotLight->SetAttenuationRadius(1000.0f); // How far the light reaches
    SpotLight->SetRelativeLocation(FVector(-200.0f, 0.0f, 0.0f)); // Position it to the right of the actor

    // Create and initialize the pickup component
    //PickupComponent = CreateDefaultSubobject<UTPPickupComponent>(TEXT("PickupComponent"));
    //PickupComponent->SetupAttachment(RootComponent); // Attach PickupComponent to the root component
    Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));

    Volume->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
    Volume->SetCollisionProfileName(TEXT("OverlapAll"));
}

void AShadowPuzzle::PossesMe()
{
    // Get the player controller
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        // Possess this actor
        PlayerController->Possess(this);

        UE_LOG(LogTemp, Log, TEXT("%s has been possessed by %s"), *GetName(), *PlayerController->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("No PlayerController found to possess %s"), *GetName());
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

    // Bind movement inputs
    PlayerInputComponent->BindAxis("MoveForward", this, &AShadowPuzzle::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AShadowPuzzle::MoveRight);
}

void AShadowPuzzle::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        // Add movement in the forward direction
        //AddMovementInput(GetActorForwardVector(), Value);
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw += FMath::Clamp(NewRotation.Yaw + Value, 0.0f, 360.0f); // Clamp pitch to avoid flipping
        SetActorRotation(NewRotation);
    }
}

void AShadowPuzzle::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        // Add movement in the right direction
        //AddMovementInput(GetActorRightVector(), Value);
        FRotator NewRotation = GetActorRotation();
        NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + Value, 0.0f, 360.0f); // Clamp pitch to avoid flipping
        SetActorRotation(NewRotation);
    }
}

