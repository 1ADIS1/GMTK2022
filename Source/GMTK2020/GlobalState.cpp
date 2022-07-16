// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalState.h"

#include "GMTK2020Character.h"
#include "GMTK2020Projectile.h"

typedef void (UGlobalState::*FunctionPtrType)(FVector);

void UGlobalState::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	Super::OnWorldChanged(OldWorld, NewWorld);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("World init!"));
	if (Powers == nullptr)
	{

		funcs[0] = &UGlobalState::PrintPosition;
		funcs[1] = &UGlobalState::PrintPosition;
		funcs[2] = &UGlobalState::PrintPosition;
		funcs[3] = &UGlobalState::PrintPosition;
		funcs[4] = &UGlobalState::PrintPosition;
		funcs[5] = &UGlobalState::PrintPosition;
		
		InitializeDefaultPowers();
	}
}


UPaperSprite* UGlobalState::GetSpriteByPowerIndex(int Index) const
{
	return Sprites[Index];
}
UPaperSprite* UGlobalState::GetSpriteById(int Id) const
{
	return Powers[Id].IconSprite;
}


FString UGlobalState::GetNameOfPower(int Index) const
{
	return Powers[Index].CardName;
}

void UGlobalState::CreateEditableCube() const
{
	auto p = GetPrimaryPlayerController();
	auto pLocation = p->GetFocalLocation();
	auto pDirection = p->GetControlRotation().Vector();

	auto spawnLocation = pLocation + pDirection*500;
	
	const FRotator SpawnRotation =p->GetControlRotation();

	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	if (CubeClass!=nullptr)
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SPAWNING CUBE"));
		auto cube = GetWorld()->SpawnActor<AGMTK2020Projectile>(CubeClass,spawnLocation,SpawnRotation,ActorSpawnParams);
		cube->AdjustForDiceEditor();
	}else
	{
		
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("NOT SPAWNING CUBE"));
	}
}

int UGlobalState::GetCostOfPower(int Index) const
{
	return Powers[Index].CostToReplace;
}


void UGlobalState::InitializeDefaultPowers()
{
	Powers = new FDicePower[6];;
	for (int i = 0; i < 6;++i)
	{
		Powers[i].Initialize(i,this);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("" + Powers[i].CardName));
	}
}

void UGlobalState::PrintPosition(FVector vec)
{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("" + vec.ToString()));
}


void UGlobalState::ExecuteFunctionByPowerIndex(int index,FVector vec)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::FromInt(index));
	//Special Thanks to Epic for this Syntax
	(this->* (funcs[Powers[index].id]))(vec);
}

void UGlobalState::ExecuteFunctionById(int id,FVector vec)
{
	//Special Thanks to Epic for this Syntax
	(this->* (funcs[id]))(vec);
}


void FDicePower::Initialize(int Id, UGlobalState* glob)
{
	this->id=Id;
	this->globalState = glob;
	this->IconSprite = glob->GetSpriteById(Id);
	
	CostToReplace = glob->Costs[Id];
	CardName = glob->Names[Id];
}

void FDicePower::ActivateAbility(FVector Position)
{
	globalState->ExecuteFunctionById(id,Position);
}

