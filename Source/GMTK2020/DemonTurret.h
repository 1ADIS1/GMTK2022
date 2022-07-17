// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "DemonTurret.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GMTK2020_API UDemonTurret : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDemonTurret();
	void Shoot();
	void Die();

	UPROPERTY(EditDefaultsOnly, Category=Effects)
	TSubclassOf<class AGenericProjectile> ProjectileType;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
