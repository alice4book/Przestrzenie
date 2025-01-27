// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Fuse.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	TArray<AActor*> ConnectedLights;

	// Sets default values for this actor's properties
	AFuseboxPuzzle();

	void PossesMe();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Interact(const FInputActionValue& Value);

	UFUNCTION()
	void CheckSolution();

	void SpawnFuses();

	bool isSolved = false;

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

	TArray<AFuse*> Fuses;
	const float FuseSpacingHorizontal = 50.0f;
	const float FuseSpacingVertical = 70.0f;
};
