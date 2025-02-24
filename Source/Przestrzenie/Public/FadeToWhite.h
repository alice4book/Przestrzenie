// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShadowPuzzle.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "LevelSequenceActor.h"
#include "FadeToWhite.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVariableChanged, bool, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVariable2Changed, bool, NewValue);

UCLASS()
class PRZESTRZENIE_API AFadeToWhite : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFadeToWhite();

	void Fade();

	void Steam();

	UFUNCTION()
	void CheckIfSolved();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle TimerHandleForFade;

	FTimerHandle TimerHandleForSteam;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FadeToWhite")
	bool isFading = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FadeToWhite")
	bool isSteaming = false;

	UPROPERTY(BlueprintAssignable, Category = "FadeToWhite")
	FOnVariableChanged OnVariableChanged;

	UPROPERTY(BlueprintAssignable, Category = "FadeToWhite")
	FOnVariableChanged OnVariable2Changed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FadeToWhite")
	TArray<AShadowPuzzle*> ShadowPuzzles;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FadeToWhite")
	ULevelSequence* FadeSequence;


};
