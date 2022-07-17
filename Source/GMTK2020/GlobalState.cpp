// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalState.h"

#include "DemonChar.h"
#include "EngineUtils.h"
#include "GMTK2020Character.h"
#include "GMTK2020Projectile.h"
#include "GMTK_GameMode.h"
#include "Kismet/GameplayStatics.h"

typedef void (UGlobalState::*FunctionPtrType)(FVector);

void UGlobalState::DamagePlayer()
{
	PlayerHp--;
	if (PlayerHp <= 0)
	{
		ChangeToLevel(CurrentLevel);
	}
}

void UGlobalState::MakeExplosion(FVector vec)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("EXPLOSION"));
	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),"Demon",allActors);

	for (auto actor : allActors)
	{
		if ((actor->GetActorLocation() - vec).Size() <= 450)
		{
			auto demon = Cast<ADemonChar>(actor);
			demon->TryTakeDamage();
		}
	}
}

void UGlobalState::SpeedUpDemons(FVector vec)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DEMON FAST"));
	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),"Demon",allActors);

	for (auto actor : allActors)
	{
		if ((actor->GetActorLocation() - vec).Size() <= 450)
		{
			if (auto demon = Cast<ADemonChar>(actor))
			{
				demon->ActivateSpeedUp();
			}
		}
	}
}

void UGlobalState::FreezeDemons(FVector vec)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DEMON SLOW"));
	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),"Demon",allActors);

	for (auto actor : allActors)
	{
		if ((actor->GetActorLocation() - vec).Size() <= 450)
		{
			auto demon = Cast<ADemonChar>(actor);
			demon->ActivateSlowDown();
		}
	}
}

void UGlobalState::SpawnTurret(FVector Vector)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("TUwwET"));
	// TODO: turret spawn
}

void UGlobalState::MakeDiceDamagey(FVector Vector)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DAMAGEY DICE"));
	if (auto player = UGameplayStatics::GetPlayerPawn(GetWorld(),0))
	{
		if (auto playerChar = Cast<AGMTK2020Character>(player))
		{
			playerChar->MakeDiceDamagey();
		}
	}
}

void UGlobalState::SpawnNewDemons(FVector Vector)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("DEMON BACKUP!"));

	auto MyMode = Cast< AGMTK_GameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	MyMode->SpawnDemonsAround(3,Vector);
}

void UGlobalState::SpawnObstacles(FVector Vector)
{
	// TODO: spawn obstacle
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("OBSTACLE SPAWN"));
}

void UGlobalState::FreezePlayer(FVector Vector)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PLAYER SLOW"));
	if (auto player = UGameplayStatics::GetPlayerPawn(GetWorld(),0))
	{
		if (auto playerChar = Cast<AGMTK2020Character>(player))
		{
			playerChar->FreezePlayer();
		}
	}
}

void UGlobalState::GivePlayerAKnife(FVector Vector)
{	if (auto player = UGameplayStatics::GetPlayerPawn(GetWorld(),0))
{
	if (auto playerChar = Cast<AGMTK2020Character>(player))
	{
		playerChar->MakeEnraged();
	}
}
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PLAYER RAGE"));
}

void UGlobalState::SpeedUpPlayer(FVector Vector)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PLAYER FAST"));
	if (auto player = UGameplayStatics::GetPlayerPawn(GetWorld(),0))
	{
		if (auto playerChar = Cast<AGMTK2020Character>(player))
		{
			playerChar->SpeedUpPlayer();
		}
	}
}

void UGlobalState::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
	CurrentLevel++;
	PlayerHp = 6;
	Super::OnWorldChanged(OldWorld, NewWorld);
	if (Powers == nullptr)
	{
		funcs[0] = &UGlobalState::MakeExplosion;
		funcs[1] = &UGlobalState::SpeedUpDemons;
		funcs[2] = &UGlobalState::FreezeDemons;
		funcs[3] = &UGlobalState::SpawnTurret;
		funcs[4] = &UGlobalState::MakeDiceDamagey;
		funcs[5] = &UGlobalState::SpawnNewDemons;
		funcs[6] = &UGlobalState::SpawnObstacles;
		funcs[7] = &UGlobalState::FreezePlayer;
		funcs[8] = &UGlobalState::GivePlayerAKnife;
		funcs[9] = &UGlobalState::SpeedUpPlayer;

		InitializeDefaultPowers();
	}
}

int UGlobalState::GetPlayerHp()
{
	return PlayerHp;
}

bool UGlobalState::GetIsCardClicked(int Index)
{
	return CardClicked[Index];
}

void UGlobalState::ProcessCardClick(int Index)
{
	if (WaitingForCardClick && !CardClicked[Index] && !IsFinishVisible())
	{
		WaitingForCardClick = false;
		PendingPowerId = CardPowerIds[Index];
		CardClicked[Index] = true;
		CardsClicked++;
	}
}

void UGlobalState::ProcessButtonClick(int Index)
{
	if (!WaitingForCardClick)
	{
		bool isDebuffPending = IsDebuff[PendingPowerId];
		if (isDebuffPending == GetIsDebuffOfPower(Index))
		{
			if (GetCostOfPower(Index) <= Blood)
			{
				WaitingForCardClick = true;
				Blood -= GetCostOfPower(Index);
				
				Powers[Index] = *(new FDicePower());
				Powers[Index].Initialize(PendingPowerId,this);

				RotatingCube->InitSides();
			}
		}
	}
}
UPaperSprite* UGlobalState::GetFullCardByPowerIndex(int Index) const
{
	return Powers[Index].FullCardSprite;
}

UPaperSprite* UGlobalState::GetFullCardByCardIndex(int Index) const
{
	return FullCards[CardPowerIds[Index]];
}

bool UGlobalState::GetIsDebuffOfPower(int Index) const
{
	return Powers[Index].IsDebuff;
}
bool UGlobalState::IsFinishVisible() const
{
	return WaitingForCardClick && CardsClicked >= 2;
}

void UGlobalState::ProcessFinishClick()
{
	FLatentActionInfo LatentInfo;
	ChangeToLevel(CurrentLevel+1);
}


UPaperSprite* UGlobalState::GetSpriteByPowerIndex(int Index) const
{
	return Powers[Index].IconSprite;
}
UPaperSprite* UGlobalState::GetSpriteById(int Id) const
{
	return Sprites[Id];
}


FString UGlobalState::GetNameOfPower(int Index) const
{
	return Powers[Index].CardName;
}

template<typename T>
void FindAllActors(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<T> It(World); It; ++It)
	{
		Out.Add(*It);
	}
}

void UGlobalState::CreateEditableCube()
{
	CardsClicked = 0;
	CardClicked[0]=false;
	CardClicked[1]=false;
	CardClicked[2]=false;
	WaitingForCardClick = true;

	CardPowerIds[0]=rand()%Names.Num();
	CardPowerIds[1]=rand()%Names.Num();
	CardPowerIds[2]=rand()%Names.Num();
	

	//Set Spawn Collision Handling Override
	FActorSpawnParameters ActorSpawnParams;
	if (CubeClass!=nullptr)
	{
		TArray<AActor*> allActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(),"DestroyOnUi",allActors);
		for (auto actor : allActors)
		{
			if (actor != nullptr)
				actor->Destroy();
		}
		GetPrimaryPlayerController()->bShowMouseCursor = true;
		GetPrimaryPlayerController()->bEnableMouseOverEvents = true;
		
		auto p = GetPrimaryPlayerController();
		auto pLocation = p->GetFocalLocation();
		auto pDirection = p->GetControlRotation().Vector();

		auto spawnLocation = pLocation + pDirection*100;
	
		const FRotator SpawnRotation =p->GetControlRotation();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SPAWNING CUBE"));
		RotatingCube = GetWorld()->SpawnActor<AGMTK2020Projectile>(CubeClass,spawnLocation,SpawnRotation,ActorSpawnParams);
		RotatingCube->AdjustForDiceEditor();
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
	this->IsDebuff = glob->IsDebuff[Id];
	this->FullCardSprite = glob->FullCards[Id];
	CostToReplace = glob->Costs[Id];
	CardName = glob->Names[Id];
}

void FDicePower::ActivateAbility(FVector Position)
{
	globalState->ExecuteFunctionById(id,Position);
}

