// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TurretChar.generated.h"

UCLASS()
class GMTK2020_API ATurretChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATurretChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Shoot();
	void Die();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	UPROPERTY(EditDefaultsOnly, Category=Effects)
	TSubclassOf<class AGenericProjectile> ProjectileType;

	UPROPERTY(EditDefaultsOnly,Category=Effects)
	FVector spawnOffset;
};
