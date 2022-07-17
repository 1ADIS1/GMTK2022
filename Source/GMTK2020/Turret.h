// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Turret.generated.h"

UCLASS()
class GMTK2020_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

	UPROPERTY(EditDefaultsOnly, Category=Effects)
	TSubclassOf<class AActor> ProjectileType;

	UPROPERTY(EditDefaultsOnly,Category=Effects)
	FVector spawnOffset;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Shoot();
	void Die();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
