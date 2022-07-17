// Fill out your copyright notice in the Description page of Project Settings.


#include "DemonChar.h"

#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ADemonChar::ADemonChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADemonChar::BeginPlay()
{
	Super::BeginPlay();
	InitializeMaterial(0);
}

void ADemonChar::TryTakeDamage()
{
	if (InvinsibilityFrameDurationLeft <= 0) 
	{
		InvinsibilityFrameDurationLeft = invinsibilityFrameDurationTotal;
		Hp--;
		if (Hp <= 0)
			Destroy();
		
	}
}

// Called every frame
void ADemonChar::Tick(float DeltaTime)
{
	InvinsibilityFrameDurationLeft -= DeltaTime;
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADemonChar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADemonChar::ActivateSpeedUp()
{
	auto charMov = FindComponentByClass<UCharacterMovementComponent>();
	if (DefaultCharSpeed == -1)
	{
		DefaultCharSpeed = charMov->MaxWalkSpeed;
	}
	if (charMov->MaxWalkSpeed != DefaultCharSpeed)
	{
		return;
	}
	charMov->MaxWalkSpeed = DefaultCharSpeed*2;
	
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle,
		this,
		&ADemonChar::ResetSpeed,
		3.0f,
		false
	);
	InitializeMaterial(2);
}

void ADemonChar::ResetSpeed()
{
	
	auto charMov = FindComponentByClass<UCharacterMovementComponent>();
	charMov->MaxWalkSpeed = DefaultCharSpeed;
	InitializeMaterial(0);
	
}

void ADemonChar::ActivateSlowDown()
{
	auto charMov = FindComponentByClass<UCharacterMovementComponent>();
	if (DefaultCharSpeed == -1)
	{
		DefaultCharSpeed = charMov->MaxWalkSpeed;
	}
	if (charMov->MaxWalkSpeed != DefaultCharSpeed)
	{
		return;
	}
	charMov->MaxWalkSpeed = DefaultCharSpeed*0.5;
	
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(
		UnusedHandle,
		this,
		&ADemonChar::ResetSpeed,
		3.0f,
		false
	);
	InitializeMaterial(1);
}
