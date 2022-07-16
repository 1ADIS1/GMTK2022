// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"

#include "Blueprint/UserWidget.h"
#include "Misc/OutputDeviceNull.h"

#include "GMTK_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class GMTK2020_API AGMTK_GameMode : public AGameMode
{
public:
	GENERATED_BODY()


	AGMTK_GameMode();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	// Level spawner

	UPROPERTY(EditAnywhere)
		TSubclassOf<APawn> Object_To_Spawn;

	UPROPERTY(EditAnywhere)
		float Spawn_Z;

	UPROPERTY(EditAnywhere)
		float Spawn_X_Min;

	UPROPERTY(EditAnywhere)
		float Spawn_X_Max;

	UPROPERTY(EditAnywhere)
		float Spawn_Y_Min;

	UPROPERTY(EditAnywhere)
		float Spawn_Y_Max;

	// Level Timer

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Level_Max_Time = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		float Level_Time_Drain = 1.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Level_Current_Time = 0.f;

	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> Level_Timer_Widget_Class;
	UUserWidget* Level_Timer_Widget;

	// Dice editor
	UPROPERTY(EditAnywhere, Category = "UI HUD")
		TSubclassOf<UUserWidget> Dice_Editor_Widget_Class;
	UUserWidget* Dice_Editor_Widget;

	bool bLevelCompleted;

	void SpawnCooldown();

	void OnLevelComplete();

	void DisplayLevelTimer();

	void DisplayDiceEditor();
};
