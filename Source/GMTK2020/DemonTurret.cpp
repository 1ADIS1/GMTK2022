// Fill out your copyright notice in the Description page of Project Settings.


#include "DemonTurret.h"

#include "GenericProjectile.h"
#include "GMTK2020Character.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UDemonTurret::UDemonTurret()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UDemonTurret::Shoot()
{


	TArray<AActor*> allActors;
	auto playerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(),0);

	if (playerPawn)
	{
		if (auto player = Cast<AGMTK2020Character>(playerPawn))
		{
			auto len = (player->GetActorLocation() - GetComponentLocation()).Size();
			if (len < 700)
			{
				FActorSpawnParameters Parameters;
				auto proj = GetWorld()->SpawnActor<AGenericProjectile>(ProjectileType,GetComponentLocation() ,GetComponentRotation(),Parameters);
				if (proj)
				{
					proj->InitAll(proj->GetActorLocation(),player->GetActorLocation(),"Player");
				}	
			}
		}
	}
	
	FTimerHandle UnusedHandle;
	GetWorld()->GetTimerManager().SetTimer(
		UnusedHandle,
		this,
		&UDemonTurret::Shoot,
		1.0f,
		false
	);
}



// Called when the game starts
void UDemonTurret::BeginPlay()
{
	Super::BeginPlay();

	Shoot();
	// ...
	
}


// Called every frame
void UDemonTurret::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

