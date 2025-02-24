// Fill out your copyright notice in the Description page of Project Settings.


#include "FadeToWhite.h"

// Sets default values
AFadeToWhite::AFadeToWhite()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AFadeToWhite::Fade()
{
	if (FadeSequence)
	{
		
		ALevelSequenceActor* SequenceActor;
		ULevelSequencePlayer* SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
			GetWorld(), FadeSequence, FMovieSceneSequencePlaybackSettings(), SequenceActor
		);

		if (SequencePlayer)
		{
			isFading = true;
			OnVariableChanged.Broadcast(isFading);
			SequencePlayer->Play();
		}
	}
}

void AFadeToWhite::Steam()
{
	isSteaming = true;
	OnVariable2Changed.Broadcast(isSteaming);
}

void AFadeToWhite::CheckIfSolved()
{
	int32 bSolvedNr = 0;
	if (ShadowPuzzles.Num() > 0)
	{
		for (AShadowPuzzle* Puzzle : ShadowPuzzles)
		{
			if (Puzzle->GetIsSolved())
			{
				bSolvedNr += 1;
			}
		}

		if (bSolvedNr == ShadowPuzzles.Num())
		{
			GetWorld()->GetTimerManager().ClearTimer(TimerHandleForSteam);
			GetWorld()->GetTimerManager().SetTimer(TimerHandleForSteam, this, &AFadeToWhite::Steam, 4.0f, false);

			GetWorld()->GetTimerManager().ClearTimer(TimerHandleForFade);
			GetWorld()->GetTimerManager().SetTimer(TimerHandleForFade, this, &AFadeToWhite::Fade, 7.0f, false);
		
		}
	}

}

// Called when the game starts or when spawned
void AFadeToWhite::BeginPlay()
{
	Super::BeginPlay();

	for (AShadowPuzzle* Puzzle : ShadowPuzzles)
	{
		if (Puzzle)
		{
			Puzzle->OnCheckSolution.AddDynamic(this, &AFadeToWhite::CheckIfSolved);
		}
	}
	
}

// Called every frame
void AFadeToWhite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

