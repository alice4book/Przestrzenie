// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPickableItem.h"
#include "../PrzestrzeniePlayerController.h"
#include <EnhancedInputComponent.h>
#include "EnhancedInputSubsystems.h"
#include "Components/BoxComponent.h"



// Sets default values
AMyPickableItem::AMyPickableItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->bCastDynamicShadow = true;
	Mesh->CastShadow = true;

	Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
	Volume->SetupAttachment(Root);
	Volume->InitBoxExtent(FVector(100.0f, 100.0f, 100.0f));
	Volume->SetCollisionProfileName(TEXT("OverlapAll"));

}

void AMyPickableItem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMyPickableItem::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("To jest komunikat na ekranie!"));
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		APrzestrzeniePlayerController* PC = Cast<APrzestrzeniePlayerController>(PlayerController);
		PC->ItemArray.Add(ItemId);
		this->Destroy();
	}
}


// Called when the game starts or when spawned
void AMyPickableItem::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		EnableInput(PlayerController);
	}
	
}

// Called every frame
void AMyPickableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

