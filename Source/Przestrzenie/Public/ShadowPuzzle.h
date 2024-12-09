// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ShadowPuzzle.generated.h"

class USpotLightComponent;
class UBoxComponent;
class UCameraComponent;
class UInputComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class PRZESTRZENIE_API AShadowPuzzle : public APawn
{
	GENERATED_BODY()

public:

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Interaction Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InteractAction;

	// Sets default values for this pawn's properties
	AShadowPuzzle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Rotate(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

	void PossesMe();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandleForSolutionCheck;
private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Plane;

	UPROPERTY(EditAnywhere)
	UBoxComponent* Volume;

	// Spotlight Component
	UPROPERTY(EditAnywhere, Category = "Lighting")
	USpotLightComponent* SpotLight;

	UPROPERTY(EditAnywhere, Category = Camera)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere)
	APawn* PreviousPawn;

	USceneComponent* Root;

	UPROPERTY(EditAnywhere, Category = "Solution")
	FRotator Solution;

	UPROPERTY(EditAnywhere, Category = "Solution")
	float PossibleOffset;

	UPROPERTY(EditAnywhere, Category = "Solution")
	bool bIsSolved;

	UFUNCTION()
	void CheckSolution();
};
