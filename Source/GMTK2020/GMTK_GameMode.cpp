// Fill out your copyright notice in the Description page of Project Settings.


#include "GMTK_GameMode.h"

#include "GlobalState.h"
#include "GMTK2020HUD.h"
#include "GMTK2020Character.h"
#include "UObject/ConstructorHelpers.h"

#include "GameFramework/Actor.h"

AGMTK_GameMode::AGMTK_GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<ACharacter> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGMTK2020HUD::StaticClass();

	PrimaryActorTick.bCanEverTick = true;
}

void AGMTK_GameMode::BeginPlay()
{
	Super::BeginPlay();

	// Timer for spawning demons
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle,
		this,
		&AGMTK_GameMode::SpawnCooldown,
		FMath::RandRange(1.f, 2.5f),
		true
	);

	DisplayLevelTimer();

	Level_Current_Time = Level_Max_Time;
}

void AGMTK_GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Level timer
	Level_Current_Time -= DeltaTime * Level_Time_Drain;

	if (Level_Current_Time < 0.f) {
		if (bLevelCompleted == true) return;

		bLevelCompleted = true;

		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(
			UnusedHandle,
			this,
			&AGMTK_GameMode::OnLevelComplete,
			3.0f,
			false
		);
	}
}

void AGMTK_GameMode::OnLevelComplete()
{
	DisplayDiceEditor();
}

void AGMTK_GameMode::SpawnCooldown()
{
	float RandX = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);
	float RandY = FMath::RandRange(Spawn_X_Min, Spawn_X_Max);

	FVector SpawnPosition = FVector(RandX, RandY, Spawn_Z);
	FRotator SpawnRotation = FRotator(0.f, 0.f, 0.f);

	GetWorld()->SpawnActor(Object_To_Spawn, &SpawnPosition, &SpawnRotation);
}

void AGMTK_GameMode::DisplayLevelTimer()
{
	if (Level_Timer_Widget_Class != nullptr) {
		Level_Timer_Widget = CreateWidget(GetWorld(), Level_Timer_Widget_Class);
		Level_Timer_Widget->AddToViewport();
	}
}

void AGMTK_GameMode::DisplayDiceEditor()
{
	if (Dice_Editor_Widget_Class != nullptr) {
		Dice_Editor_Widget = CreateWidget(GetWorld(), Dice_Editor_Widget_Class);
		Dice_Editor_Widget->AddToViewport();
	}
}
