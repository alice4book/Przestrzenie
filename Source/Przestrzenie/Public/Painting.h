// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FuseboxPuzzle.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Painting.generated.h"



UCLASS()
class PRZESTRZENIE_API APainting : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APainting();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeMaterialParameters(bool moving);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	AFuseboxPuzzle* FuseboxPuzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Puzzle")
	bool isMoving = true;

	UMaterialInstanceDynamic* DynamicMaterial;

	UMaterialInterface* Material;


private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* MeshComponent;


};
