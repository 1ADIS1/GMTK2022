// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "Engine/GameInstance.h"
#include "GlobalState.generated.h"

class FDicePower;
/**
 * 
 */
UCLASS()
class GMTK2020_API UGlobalState : public UGameInstance
{
	GENERATED_BODY()

private:
	
	
public:

	UPROPERTY(EditDefaultsOnly, Category=ProjectilePrime)
	TArray<UPaperSprite*> Sprites;

	UPROPERTY(EditDefaultsOnly, Category=ProjectilePrime)
	TArray<FString> Names;

	UPROPERTY(EditDefaultsOnly, Category=ProjectilePrime)
	TArray<int> Costs;
	
	void OnWorldChanged(
	UWorld* OldWorld,
	UWorld* NewWorld
) override;
	
	UPROPERTY(EditDefaultsOnly, Category=ProjectilePrime)
	TSubclassOf<class AGMTK2020Projectile> CubeClass;
	
	UFUNCTION(BlueprintCallable)
	UPaperSprite* GetSpriteById(int Id) const;
	
	UFUNCTION(BlueprintCallable)
	UPaperSprite* GetSpriteByPowerIndex(int Index) const;

	UFUNCTION(BlueprintCallable)
	FString GetNameOfPower(int Index) const;

	UFUNCTION(BlueprintCallable)
	void CreateEditableCube() const;
	
	UFUNCTION(BlueprintCallable)
	int GetCostOfPower(int Index) const;
	

	
	FDicePower* Powers = nullptr;
	void InitializeDefaultPowers();
	void PrintPosition(FVector vec);

	void ExecuteFunctionById(int id,FVector vec);
	void ExecuteFunctionByPowerIndex(int powerIndex,FVector vec);
	
	typedef void (UGlobalState::*FunctionPtrType)(FVector);

	
	FunctionPtrType funcs[1000];
};
	
typedef void (UGlobalState::*FunctionPtrType)(FVector);

class FDicePower
{
public:
	UGlobalState* globalState;
	void Initialize(int Id, UGlobalState* glob);
	void ActivateAbility(FVector Position);
	int CostToReplace;
	FString CardName;
	UPaperSprite* IconSprite;
	int id;
private:
	FunctionPtrType func;
};
