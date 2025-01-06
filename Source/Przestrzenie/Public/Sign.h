// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sign.generated.h"

UCLASS()
class PRZESTRZENIE_API ASign : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASign();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuse")
	int32 SignVariant;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuse")
	TArray<UMaterialInstance*> MaterialVariants;

	int32 GetSignIndex() const { return SignIndex; }

	void SetSignVariant(int32 variant) { SignVariant = variant; }

	void SetSignMaterial();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuse")
	int32 SignIndex;

private:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* Cube;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
