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



FString UGlobalState::GetNameOfPower(int Index) const
{
	return Powers[Index].CardName;
}

void UGlobalState::CreateEditableCube() const
{
	auto p =GetPrimaryPlayerController();
	auto pLocation = p->GetFocalLocation();
	auto pDirection = p->GetControlRotation().Vector();

	auto spawnLocation = pLocation + pDirection*100;
	
	const FRotator SpawnRotation =p->GetControlRotation();

	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	if (CubeClass!=nullptr)
	{
		
		GetWorld()->SpawnActor<AGMTK2020Projectile>(CubeClass,spawnLocation,SpawnRotation,ActorSpawnParams);
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
	
	TList<FString>* names = new TList<FString>("first name",
	new TList<FString>("Second name",
	new TList<FString>("3 name",
	new TList<FString>("4 name",
	new TList<FString>("5 name",
		new TList<FString>("6 name"))))));
	TList<int>* costs = new TList<int>(1,
	new TList<int>(2,
	new TList<int>(3,
	new TList<int>(4,
	new TList<int>(5,
		new TList<int>(6))))));;
	
	auto initialNames = names;
	auto initialCosts = costs;
	
	for (int i = 0; i < Id;++i)
	{
		costs = costs->Next;
		names = names->Next;
	}
	CostToReplace = costs->Element;
	CardName = names->Element;
	delete initialCosts;
	delete initialNames;
}

void FDicePower::ActivateAbility(FVector Position)
{
	globalState->ExecuteFunctionById(id,Position);
}

