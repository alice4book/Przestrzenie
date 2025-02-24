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

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckSolutionDelegate);

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

	/** Interaction Input Change Object */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChangeObjectAction;

	// Sets default values for this pawn's properties
	AShadowPuzzle();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Rotate(const FInputActionValue& Value);

	void Interact(const FInputActionValue& Value);

	void ChangeObject(const FInputActionValue& Value);

	void PossesMe();

	bool GetIsSolved();

	UPROPERTY()
	FOnCheckSolutionDelegate OnCheckSolution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	bool isInteracting = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandleForSolutionCheck;
private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* CurrentMesh;

	UPROPERTY(EditAnywhere, Category = "ShadowPuzzle")
	UStaticMesh* Mesh1;

	UPROPERTY(EditAnywhere, Category = "ShadowPuzzle")
	UStaticMesh* Mesh2;

	UPROPERTY(EditAnywhere, Category = "ShadowPuzzle")
	UStaticMesh* Mesh3;

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

	UPROPERTY(EditAnywhere, Category = "Solution")
	int SolutionSize;

	UPROPERTY(EditAnywhere, Category = "Solution")
	int CurrentSize = 0;

	int32 CurrentIndex = 0;

	UFUNCTION()
	void CheckSolution();
};
