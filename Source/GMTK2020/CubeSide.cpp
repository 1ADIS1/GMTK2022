// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeSide.h"
#include "PaperSpriteComponent.h"

// Sets default values for this component's properties
UCubeSide::UCubeSide()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	icon = CreateDefaultSubobject<UPaperSpriteComponent>("Icon");
	icon->SetupAttachment(this);
	icon->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
	icon->SetRelativeScale3D(FVector(0.5,0.5,0.5));
	// ...
}


// Called when the game starts
void UCubeSide::BeginPlay()
{
	Super::BeginPlay();
	// ...
	
}


// Called every frame
void UCubeSide::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

