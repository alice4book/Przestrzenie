// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FuseboxPuzzle.generated.h"

class UBoxComponent;
class UCameraComponent;
class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class PRZESTRZENIE_API AFuseboxPuzzle : public APawn
{
	GENERATED_BODY()
	
public:	

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	// Sets default values for this actor's properties
	AFuseboxPuzzle();

	void PossesMe();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Interact(const FInputActionValue& Value);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	USceneComponent* Root;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Cube;

	UPROPERTY(EditAnywhere, Category = Camera)
	UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Volume;

	UPROPERTY(VisibleAnywhere)
	APawn* PreviousPawn;
};
