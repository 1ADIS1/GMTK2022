// Copyright Epic Games, Inc. All Rights Reserved.

#include "GMTK2020GameMode.h"
#include "GMTK2020HUD.h"
#include "GMTK2020Character.h"
#include "UObject/ConstructorHelpers.h"

AGMTK2020GameMode::AGMTK2020GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGMTK2020HUD::StaticClass();
}
