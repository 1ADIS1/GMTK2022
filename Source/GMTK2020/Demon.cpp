// Fill out your copyright notice in the Description page of Project Settings.


#include "Demon.h"

#include "AIController.h"
#include "GameFramework/PawnMovementComponent.h"

// Sets default values
ADemon::ADemon()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// PawnMovementComponent= CreateDefaultSubobject<UPawnMovementComponent>("Pawn movement");
}

// Called when the game starts or when spawned
void ADemon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADemon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

if (auto controller = GetController())
	{
		if (auto aiController =  Cast<AAIController>(controller))
		{
			auto movementVector =150*DeltaTime* (aiController->GetImmediateMoveDestination()- GetActorLocation());
			auto baseLocation = GetActorLocation();
			//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Target is ..." +aiController->GetImmediateMoveDestination().ToString()));
			//SetActorLocation(baseLocation+movementVector);
			// if (Player != nullptr)
			// {
			// 	auto moveVectorMagnitude = movementVector.Size();
			//
			// 	//if (moveVectorMagnitude > 0.01)
			// 	//{
			// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Move vec magnitude is ..." + FString::SanitizeFloat(moveVectorMagnitude)));
			// 	//}
			// 	movementVector.Normalize();
			// 	CubeMesh->AddImpulse(movementVector * 5000);
			// }else{
			// 	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Could not find APlayerController... very sadge..."));
			//
			// }
		}
	}
	
	
}

// Called to bind functionality to input
void ADemon::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

