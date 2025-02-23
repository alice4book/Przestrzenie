// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "../PrzestrzeniePlayerController.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include <EnhancedInputComponent.h>
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Cube = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	//RootComponent = Cube;
	Cube->SetupAttachment(Root);

	UStaticMesh* CubeMesh = ConstructorHelpers::FObjectFinder<UStaticMesh>(TEXT("/Engine/BasicShapes/Cube.Cube")).Object;

	Cube->SetStaticMesh(CubeMesh);
	Cube->bCastDynamicShadow = true;
	Cube->CastShadow = true;

	Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
	Volume->SetupAttachment(Root);
	Volume->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	Volume->SetCollisionProfileName(TEXT("OverlapAll"));

	RotationSpeed = 2.0f;
	IsRotating = false;
	RotationAlpha = 0.0f;
	IsOpen = false;

}

void ADoor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADoor::Interact()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		APrzestrzeniePlayerController* PC = Cast<APrzestrzeniePlayerController>(PlayerController);
		if (PC->ItemArray.Contains(1)) //1 is the id of a key
		{
			IsRotating = true;
			// Play door opening sound (if set in BP)
			if (OpenSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, OpenSound, GetActorLocation());
			}
		}
		else
		{
			// Play locked sound when player doesn't have the key (if set in BP)
			if (LockedSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, LockedSound, GetActorLocation());
			}
		}
	}
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

	StartRotation = Cube->GetRelativeRotation();
	
}

// Called every frame
void ADoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsRotating && !IsOpen)
	{
		RotationAlpha += DeltaTime * RotationSpeed;
		if (RotationAlpha >= 1.0f)
		{
			RotationAlpha = 1.0f;
			IsRotating = false;
			IsOpen = true;
		}

		FRotator NewRotation = FRotator(StartRotation.Pitch, FMath::Lerp(StartRotation.Yaw, TargetRotation.Yaw, RotationAlpha), StartRotation.Roll);
		Cube->SetRelativeRotation(NewRotation);
	}

}

void ADoor::Rotate()
{

}

