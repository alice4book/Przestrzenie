// Copyright Epic Games, Inc. All Rights Reserved.

#include "PrzestrzenieGameMode.h"
#include "PrzestrzenieCharacter.h"
#include "UObject/ConstructorHelpers.h"

APrzestrzenieGameMode::APrzestrzenieGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
