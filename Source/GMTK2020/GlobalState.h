// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "Engine/GameInstance.h"
#include "GlobalState.generated.h"

class AGMTK2020Projectile;
class FDicePower;
/**
 * 
 */
UCLASS()
class GMTK2020_API UGlobalState : public UGameInstance
{
	GENERATED_BODY()

private:
	int CardsClicked = 0;
	
	bool CardClicked[3]{false,false,false};

	int PendingPowerId = 0;

	int CurrentLevel = -1;
	
	int CardPowerIds[3]{0,0,0};
	
	bool WaitingForCardClick = false;

	AGMTK2020Projectile* RotatingCube = nullptr;
	
public:

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeToLevel(int LevelIndex);
	
	UPROPERTY(EditAnywhere,Category=Blood)
	int Blood = 100;

	UPROPERTY(EditDefaultsOnly, Category=ProjectilePrime)
	TArray<UPaperSprite*> Sprites;
	
	UPROPERTY(EditDefaultsOnly, Category=ProjectilePrime)
	TArray<UPaperSprite*> FullCards;

	UPROPERTY(EditDefaultsOnly, Category=ProjectilePrime)
	TArray<FString> Names;
	
	UPROPERTY(EditDefaultsOnly, Category=ProjectilePrime)
	TArray<bool> IsDebuff;

	UPROPERTY(EditDefaultsOnly, Category=ProjectilePrime)
	TArray<int> Costs;
	
	UPROPERTY(EditDefaultsOnly, Category=ProjectilePrime)
	TArray<FName> Levels;
	
	void OnWorldChanged(
	UWorld* OldWorld,
	UWorld* NewWorld
) override;
	
	UPROPERTY(EditDefaultsOnly, Category=ProjectilePrime)
	TSubclassOf<class AGMTK2020Projectile> CubeClass;


	
	UFUNCTION(BlueprintCallable)
	bool GetIsCardClicked(int Index);
	UFUNCTION(BlueprintCallable)
	void ProcessCardClick(int Index);
	UFUNCTION(BlueprintCallable)
	void ProcessButtonClick(int Index);

	
	UFUNCTION(BlueprintCallable)
	bool IsFinishVisible() const;
	
	UFUNCTION(BlueprintCallable)
	void ProcessFinishClick();
	
	UFUNCTION(BlueprintCallable)
	UPaperSprite* GetSpriteById(int Id) const;
	
	UFUNCTION(BlueprintCallable)
	UPaperSprite* GetSpriteByPowerIndex(int Index) const;
	
	UFUNCTION(BlueprintCallable)
	UPaperSprite* GetFullCardByPowerIndex(int Index) const;
	UFUNCTION(BlueprintCallable)
	UPaperSprite* GetFullCardByCardIndex(int Index) const;


	UFUNCTION(BlueprintCallable)
	FString GetNameOfPower(int Index) const;

	UFUNCTION(BlueprintCallable)
	void CreateEditableCube();
	
	UFUNCTION(BlueprintCallable)
	int GetCostOfPower(int Index) const;
	
	UFUNCTION(BlueprintCallable)
	int GetIsDebuffOfPower(int Index) const;
	

	
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
	UPaperSprite* FullCardSprite;
	UPaperSprite* IconSprite;
	bool IsDebuff;
	int id;
private:
	FunctionPtrType func;
};
