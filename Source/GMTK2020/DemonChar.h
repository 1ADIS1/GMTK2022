// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Misc/OutputDeviceNull.h"

#include "DemonChar.generated.h"

UCLASS()
class GMTK2020_API ADemonChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADemonChar();

	
	void Shoot();
	void Die();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	int DefaultCharSpeed = -1;
	int InvinsibilityFrameDurationLeft = 0;
	int invinsibilityFrameDurationTotal = 1;
public:
	UFUNCTION(BlueprintImplementableEvent)
	void InitializeMaterial(int status);
	
	
	UPROPERTY(EditAnywhere)
	int Hp = 1;

	void TryTakeDamage();
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ActivateSpeedUp();
	void ResetSpeed();
	void ActivateSlowDown();

	UPROPERTY(EditAnywhere, Category = "BlueprintClass")
		AActor* blueprintActor;

	UFUNCTION(BlueprintImplementableEvent)
		void PlayDamageSound();
	
	UFUNCTION(BlueprintImplementableEvent)
		void PlayDeathSound();

};
