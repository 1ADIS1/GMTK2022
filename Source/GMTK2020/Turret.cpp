// Fill out your copyright notice in the Description page of Project Settings.


#include "Turret.h"

#include "DemonChar.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();

	Shoot();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle,
		this,
		&ATurret::Die,
		8.0f,
		false
	);
	
}

void ATurret::Shoot()
{

	
	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),"Demon",allActors);

	ADemonChar * closestDemon = nullptr;
	float closestDistance = 99999.0;
	
	for (auto actor : allActors)
	{
		auto len = (actor->GetActorLocation() - GetActorLocation()).Size();
		if (len <= closestDistance && len < 700)
		{
			if (auto demon = Cast<ADemonChar>(actor))
			{
				closestDemon = demon;
				closestDistance = len;
			}
		}
	}

	FActorSpawnParameters Parameters;
	
	GetWorld()->SpawnActor<AActor>(ProjectileType,GetActorLocation() + spawnOffset,GetActorRotation(),Parameters);
	
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle,
		this,
		&ATurret::Shoot,
		1.0f,
		false
	);
}

void ATurret::Die()
{
	Destroy();
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

