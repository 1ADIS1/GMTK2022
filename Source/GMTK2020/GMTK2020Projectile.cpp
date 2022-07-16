// Copyright Epic Games, Inc. All Rights Reserved.

#include "GMTK2020Projectile.h"

#include "GlobalState.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AGMTK2020Projectile::AGMTK2020Projectile() 
{
	PrimaryActorTick.bCanEverTick = true;
	
	staticMesh = CreateDefaultSubobject<UStaticMeshComponent>("CubeMesh");
	
	// Set as root component
	RootComponent = staticMesh;
	
	// Use a sphere as a simple collision representation
	//staticMesh->BodyInstance.SetCollisionProfileName("Projectile");
	staticMesh->OnComponentHit.AddDynamic(this, &AGMTK2020Projectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	staticMesh->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	staticMesh->CanCharacterStepUpOn = ECB_No;

	// Die after many seconds by default
	InitialLifeSpan = 999.0f;

	
	FirstSide = CreateDefaultSubobject<UCubeSide>(TEXT("Side1"));
	FirstSide->SetupAttachment(staticMesh);
	
	SecondSide = CreateDefaultSubobject<UCubeSide>(TEXT("Side2"));
	SecondSide->SetupAttachment(staticMesh);
	
	ThirdSide = CreateDefaultSubobject<UCubeSide>(TEXT("Side3"));
	ThirdSide->SetupAttachment(staticMesh);
	
	FourthSide = CreateDefaultSubobject<UCubeSide>(TEXT("Side4"));
	FourthSide->SetupAttachment(staticMesh);
	
	FifthSide = CreateDefaultSubobject<UCubeSide>(TEXT("Side5"));
	FifthSide->SetupAttachment(staticMesh);
	
	SixthSide = CreateDefaultSubobject<UCubeSide>(TEXT("Side6"));
	SixthSide->SetupAttachment(staticMesh);
	
}

void AGMTK2020Projectile::OnShoot(FVector originLocation)
{

	inited = true;
	
	auto physicsActor = Cast<UStaticMeshComponent>(this->GetRootComponent());

	physicsActor->AddImpulse(GetActorRotation().Vector()*300000);
	
	FVector SpawnVector;
	SpawnVector.X = FMath::FRandRange(-10000, 10000);
	SpawnVector.Y = FMath::FRandRange(-10000, 10000);
	SpawnVector.Z = FMath::FRandRange(-10000, 10000);
	
	physicsActor->AddAngularImpulseInRadians(SpawnVector);
}


int AGMTK2020Projectile::GetIdOfLowestSide()
{
		UE_LOG(LogTemp, Warning, TEXT("SSec"));
	auto pairs = {
		std::pair<UCubeSide*,int>(FirstSide,0),
		std::pair<UCubeSide*,int>(SecondSide,1),
		std::pair<UCubeSide*,int>(ThirdSide,2),
		std::pair<UCubeSide*,int>(FourthSide,3),
		std::pair<UCubeSide*,int>(FifthSide,4),
		std::pair<UCubeSide*,int>(SixthSide,5),
	};
		UE_LOG(LogTemp, Warning, TEXT("SSec2"));
	int height = INT_MAX;
	int id = -1;
	for (auto Pair : pairs)
	{
		UE_LOG(LogTemp, Warning, TEXT("SSec3"));
		int curHeight = Pair.first->GetComponentLocation().Z;
		if (curHeight < height)
		{
		UE_LOG(LogTemp, Warning, TEXT("SSec4"));
			height = curHeight;
			id = Pair.second;
		}
	}
		UE_LOG(LogTemp, Warning, TEXT("third"));
	return id;
}

void AGMTK2020Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}


// Called every frame
void AGMTK2020Projectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (inited && staticMesh->GetPhysicsLinearVelocity().Size()<10 && cont++ >= 2)
	{
		UE_LOG(LogTemp, Warning, TEXT("FirstHeyHey"));
		int indexToExecute = GetIdOfLowestSide();
		Cast<UGlobalState>(GetGameInstance())->ExecuteFunctionByPowerIndex(indexToExecute, GetActorLocation());
		Destroy();
	}
}