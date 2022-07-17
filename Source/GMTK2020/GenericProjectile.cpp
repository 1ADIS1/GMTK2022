// Fill out your copyright notice in the Description page of Project Settings.


#include "GenericProjectile.h"

#include "DemonChar.h"
#include "GMTK2020Character.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AGenericProjectile::AGenericProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AGenericProjectile::InitAll(FVector from, FVector to,FName tagToKill)
{
	this->TagToKill = tagToKill;
	
	auto projMov = FindComponentByClass<UProjectileMovementComponent>();
	auto vel = (from-to);
	vel.Normalize();

	projMov->Velocity = -vel*projMov->InitialSpeed;

	
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle,
		this,
		&AGenericProjectile::Die,
		8.0f,
		false
	);
}


void AGenericProjectile::Die()
{
	Destroy();
}


// Called when the game starts or when spawned
void AGenericProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGenericProjectile::ProcessOverlap(AActor* otherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, otherActor->GetHumanReadableName());
	if (otherActor->ActorHasTag(TagToKill))
	{
		if (auto pl = Cast<AGMTK2020Character>(otherActor))
		{
			pl->TryTakeDamage();
		}else if (auto demon = Cast<ADemonChar>(otherActor))
		{
			demon->TryTakeDamage();
		}
		Destroy();
	}
}

// Called every frame
void AGenericProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
