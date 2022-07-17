// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DemonChar.generated.h"

UCLASS()
class GMTK2020_API ADemonChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ADemonChar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	int DefaultCharSpeed = -1;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void ActivateSpeedUp();
	void ResetSpeed();
};
