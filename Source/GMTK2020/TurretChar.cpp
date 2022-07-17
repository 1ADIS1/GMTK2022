// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretChar.h"

#include "DemonChar.h"
#include "GenericProjectile.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ATurretChar::ATurretChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATurretChar::BeginPlay()
{
	Super::BeginPlay();
	

	Shoot();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle,
		this,
		&ATurretChar::Die,
		8.0f,
		false
	);
}

void ATurretChar::Shoot()
{

	
	TArray<AActor*> allActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(),"Demon",allActors);

	auto statMesh = FindComponentByClass<UStaticMeshComponent>();

	
	ADemonChar * closestDemon = nullptr;
	float closestDistance = 99999.0;
	
	for (auto actor : allActors)
	{
		auto len = (actor->GetActorLocation() - statMesh->GetComponentLocation()).Size();
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
	if (closestDemon != nullptr)
	{
		auto proj = GetWorld()->SpawnActor<AGenericProjectile>(ProjectileType,statMesh->GetComponentLocation()+ spawnOffset,GetActorRotation(),Parameters);
		if (proj)
		{
			proj->InitAll(proj->GetActorLocation(),closestDemon->GetActorLocation(),"Demon");
		}
	}

	
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle,
		this,
		&ATurretChar::Shoot,
		1.0f,
		false
	);
}

void ATurretChar::Die()
{
	Destroy();
}


// Called every frame
void ATurretChar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATurretChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

