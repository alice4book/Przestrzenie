// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sign.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fuse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFuseRotatedDelegate);

UCLASS()
class PRZESTRZENIE_API AFuse : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuse();
	AFuse(int up, int right, int down, int left);

	UPROPERTY()
	FOnFuseRotatedDelegate OnRotate;

	void Rotate();

	UFUNCTION()
	void OnFuseClicked(AActor* TouchedActor, FKey ButtonPressed);

	int32 GetFuseIndex() const { return FuseIndex; }

	int32 GetSignValue(int32 Side) const { return CurrentRotationSigns[Side]; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuse")
	int32 FuseIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuse")
	TArray<int> SignValues;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuse")
	//TArray<ASign*> Signs;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuse")
	TArray<int> CurrentRotationSigns;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuse",
		meta = (DisplayName = "Neighbour Fuse Index, Orientation(up0,right1,down2,left3)"))
	TMap<int32, int32> NeighbourFuses;

	int RotationIndex;

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Cube;

	USceneComponent* Root;

	FRotator TargetRotation;

	UPROPERTY(EditAnywhere)
	float RotationSpeed;

	bool IsRotating;

	float RotationAlpha;

	FRotator StartRotation;

};
