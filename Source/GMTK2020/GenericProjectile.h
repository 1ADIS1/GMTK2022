// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GenericProjectile.generated.h"

UCLASS()
class GMTK2020_API AGenericProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGenericProjectile();
	void InitAll(FVector from, FVector to, FName tagToKill);
	void Die();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	FName TagToKill="";

public:
	
	UFUNCTION(BlueprintCallable)
	void ProcessOverlap(AActor* otherActor);
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
