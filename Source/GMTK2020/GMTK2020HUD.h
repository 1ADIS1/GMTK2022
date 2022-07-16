// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GMTK2020HUD.generated.h"

UCLASS()
class AGMTK2020HUD : public AHUD
{
	GENERATED_BODY()

public:
	AGMTK2020HUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

private:
	/** Crosshair asset pointer */
	class UTexture2D* CrosshairTex;

};

