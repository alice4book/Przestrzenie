// Copyright Epic Games, Inc. All Rights Reserved.

#include "PrzestrzenieCharacter.h"
#include "PrzestrzenieProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "ShadowPuzzle.h"
#include "FuseboxPuzzle.h"
#include "MyPickableItem.h"
#include "Door.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// APrzestrzenieCharacter

APrzestrzenieCharacter::APrzestrzenieCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

}

void APrzestrzenieCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
	CapsuleComponent = GetCapsuleComponent();
}

//////////////////////////////////////////////////////////////////////////// Input

void APrzestrzenieCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APrzestrzenieCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APrzestrzenieCharacter::Look);
		
		// Interact
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Started, this, &APrzestrzenieCharacter::Interact);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

// Implement Interact logic
void APrzestrzenieCharacter::Interact(const FInputActionValue& Value)
{
	TArray<AActor*> OverlappingActors;

	// Get the overlapping actors
	if (CapsuleComponent)
	{
		CapsuleComponent->GetOverlappingActors(OverlappingActors);

		// Log or process the overlapping actors
		if (OverlappingActors.Num() > 0)
		{
			for (AActor* Actor : OverlappingActors)
			{
				if (Actor)
				{
					AShadowPuzzle* puzzle = Cast<AShadowPuzzle>(Actor);
					if (puzzle)
					{
						puzzle->PossesMe();
						break;
					}

					AFuseboxPuzzle* fuseboxPuzzle = Cast<AFuseboxPuzzle>(Actor);
					if (fuseboxPuzzle)
					{
						fuseboxPuzzle->PossesMe();
						break;
					}

					AMyPickableItem* MyItem = Cast<AMyPickableItem>(Actor);
					if (MyItem) {
						MyItem->Interact();
						break;
					}

					ADoor* Door = Cast<ADoor>(Actor);
					if (Door)
					{
						Door->Interact();
						break;
					}
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Interact No actors overlapping with the capsule."));
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Interact CapsuleComponent is null!"));
	}
}

void APrzestrzenieCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void APrzestrzenieCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}