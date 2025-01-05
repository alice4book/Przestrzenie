// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Fuse.generated.h"

UCLASS()
class PRZESTRZENIE_API AFuse : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuse();
	AFuse(FString up, FString right, FString down, FString left);

	void Rotate();

	// Click event handler
	UFUNCTION()
	void OnFuseClicked(AActor* TouchedActor, FKey ButtonPressed);

	int32 GetFuseIndex() const { return FuseIndex; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuse")
	int32 FuseIndex;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	TArray<FString> Signs;

	int RotationIndex;

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Cube;

};
