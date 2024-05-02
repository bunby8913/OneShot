// Copyright Epic Games, Inc. All Rights Reserved.

#include "OneShotGameMode.h"
#include "OneShotCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOneShotGameMode::AOneShotGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
