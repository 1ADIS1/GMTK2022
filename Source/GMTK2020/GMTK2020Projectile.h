// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CubeSide.h"
#include "GameFramework/Actor.h"
#include "GMTK2020Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class AGMTK2020Projectile : public AActor
{
	GENERATED_BODY()

	/** Side */
	UPROPERTY(VisibleDefaultsOnly, Category=Sides)
	UCubeSide* FirstSide;

	/** Side */
	UPROPERTY(VisibleDefaultsOnly, Category=Sides)
	UCubeSide* SecondSide;

	/** Side */
	UPROPERTY(VisibleDefaultsOnly, Category=Sides)
	UCubeSide* ThirdSide;

	/** Side */
	UPROPERTY(VisibleDefaultsOnly, Category=Sides)
	UCubeSide* FourthSide;

	/**Side */
	UPROPERTY(VisibleDefaultsOnly, Category=Sides)
	UCubeSide* FifthSide;

	/** Side */
	UPROPERTY(VisibleDefaultsOnly, Category=Sides)
	UCubeSide* SixthSide;

public:

	UFUNCTION(BlueprintImplementableEvent)
	void InitializeMaterial(int status);
	
	/** Sphere collision component */
	UPROPERTY(BlueprintReadWrite ,EditAnywhere, Category=Projectile)
	UStaticMeshComponent* staticMesh;

	UFUNCTION(BlueprintImplementableEvent)
		void PlayDiceSound();

	/** Projectile movement component */
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	// UProjectileMovementComponent* ProjectileMovement;


private:
	bool IsDamagey = false;
	bool inited = false;
	int cont = 0;
	bool diceEditored = false;
	FVector rememberedPosition;
public:
	AGMTK2020Projectile();
	void InitSides();

	UFUNCTION(BlueprintCallable)
	void HitHappened(AActor* otherActor);


	
	void AdjustForDiceEditor();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OnShoot(FVector from, bool isDamagey);

	int GetIdOfLowestSide();
	
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};

