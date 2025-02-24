// Fill out your copyright notice in the Description page of Project Settings.


#include "ShadowPuzzle.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include <EnhancedInputComponent.h>
#include <Przestrzenie/PrzestrzeniePlayerController.h>

// Sets default values
AShadowPuzzle::AShadowPuzzle() : PreviousPawn(nullptr), Solution(FRotator(0.0f, 0.0f, 0.0f)), PossibleOffset(8.0f), bIsSolved(false)
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = Root;

    CurrentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    CurrentMesh->SetupAttachment(Root);
    CurrentMesh->bCastDynamicShadow = true;
    CurrentMesh->CastShadow = true;
    
    // Create a CameraComponent	
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(Root);
    CameraComponent->SetRelativeLocationAndRotation(
        FVector(-38.f, -43.f, -10.f), 
        FRotator(0.0f, 35.0f, 0.0f)); // Position the camera
    CameraComponent->Deactivate();
    
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
    if (PlayerController && !bIsSolved)
    {
        CameraComponent->Activate();
        PreviousPawn = PlayerController->GetPawn();
        // Possess this actor
        PlayerController->Possess(this);
        Plane->SetVisibility(true);

        isInteracting = true;
    }
}

bool AShadowPuzzle::GetIsSolved()
{
    return bIsSolved;
}

// Called when the game starts or when spawned
void AShadowPuzzle::BeginPlay()
{
	Super::BeginPlay();
    TArray<UStaticMeshComponent*> MeshComponents;
    GetComponents<UStaticMeshComponent>(MeshComponents);

    for (UStaticMeshComponent* MeshComp : MeshComponents)
    {
        if (MeshComp && MeshComp->GetName() == TEXT("Plane1"))  // Ensure MeshComp is valid
        {
            Plane = MeshComp;
            Plane->SetVisibility(false); 
            break;  // Stop searching once we find the component
        }
    }
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
        // Change object
        EnhancedInputComponent->BindAction(ChangeObjectAction, ETriggerEvent::Started, this, &AShadowPuzzle::ChangeObject);
    }
}

void AShadowPuzzle::Rotate(const FInputActionValue& Value)
{
    if (bIsSolved)
        return;
    // input is a Vector2D
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (Controller != nullptr)
    {
        GetWorld()->GetTimerManager().ClearTimer(TimerHandleForSolutionCheck);
        // Add rotation to the specific mesh component
        FRotator RotationDelta = FRotator::ZeroRotator;

        // Apply rotation based on input
        RotationDelta.Yaw = -MovementVector.X;  // Rotate around the Z-axis (yaw)
        RotationDelta.Pitch = -MovementVector.Y; // Rotate around the Y-axis (pitch)

        CurrentMesh->AddLocalRotation(RotationDelta);

        GetWorld()->GetTimerManager().SetTimer(TimerHandleForSolutionCheck, this, &AShadowPuzzle::CheckSolution, 1.0f, false);
    }
}

void AShadowPuzzle::Interact(const FInputActionValue& Value)
{
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController && PreviousPawn)
    {
        CameraComponent->Deactivate();
        Plane->SetVisibility(false);
        if (!bIsSolved) {
            CurrentMesh->SetStaticMesh(nullptr);
        }
        // Possess this actor
        PlayerController->Possess(PreviousPawn);

        isInteracting = false;
    }
}

void AShadowPuzzle::ChangeObject(const FInputActionValue& Value)
{
    APrzestrzeniePlayerController* PlayerController = Cast<APrzestrzeniePlayerController>(GetWorld()->GetFirstPlayerController());
    if (bIsSolved)
        return;
    if (PlayerController->ItemArray.IsEmpty()) {
        UE_LOG(LogTemp, Warning, TEXT("You dont have any objects."));
        return;
    }

    FVector2D MovementVector = Value.Get<FVector2D>();
    if (PlayerController)
    {
        CurrentIndex = (CurrentIndex + 1) % PlayerController->ItemArray.Num();
        CurrentSize = PlayerController->ItemArray[CurrentIndex]; // Pobierz aktualny element

        switch (CurrentSize)
        {
            case 2:
                //UE_LOG(LogTemp, Warning, TEXT("2"));
                CurrentMesh->SetStaticMesh(Mesh1);
                CurrentMesh->SetRelativeScale3D(FVector(0.7f, 0.7f, 0.7f));
                break;
            case 3:
                //UE_LOG(LogTemp, Warning, TEXT("3"));
                CurrentMesh->SetStaticMesh(Mesh2);
                CurrentMesh->SetRelativeScale3D(FVector(1.0f, 1.0f, 1.0f));
                break;
            case 4:
                //UE_LOG(LogTemp, Warning, TEXT("4"));
                CurrentMesh->SetStaticMesh(Mesh3);
                CurrentMesh->SetRelativeScale3D(FVector(1.4f, 1.4f, 1.4f));
                break;
            default:
                UE_LOG(LogTemp, Warning, TEXT("Invalid value!"));
                break;
        }
    }
}

void AShadowPuzzle::CheckSolution()
{
    FRotator CurrentRotation = CurrentMesh->GetRelativeRotation();
    if ((SolutionSize == CurrentSize) && ((FMath::Abs(CurrentRotation.Pitch - Solution.Pitch) <= PossibleOffset &&
        FMath::Abs(CurrentRotation.Yaw - Solution.Yaw) <= PossibleOffset &&
        FMath::Abs(CurrentRotation.Roll - Solution.Roll) <= PossibleOffset)
        || (FMath::Abs(CurrentRotation.Pitch - Solution.Pitch) <= PossibleOffset &&
            FMath::Abs(CurrentRotation.Yaw + 180.0f - Solution.Yaw) <= PossibleOffset &&
            FMath::Abs(CurrentRotation.Roll - Solution.Roll) <= PossibleOffset)))
    {
        bIsSolved = true;
        APrzestrzeniePlayerController* PlayerController = Cast<APrzestrzeniePlayerController>(GetWorld()->GetFirstPlayerController());
        PlayerController->ItemArray.Remove(CurrentSize);
        GEngine->AddOnScreenDebugMessage(
            -1,
            5.f,
            FColor::Green,
            TEXT("You solved it.")
        );
    }

    OnCheckSolution.Broadcast();
}

