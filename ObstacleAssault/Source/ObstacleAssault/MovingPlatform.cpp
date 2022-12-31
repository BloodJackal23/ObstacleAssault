// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	timer = 0;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	bIsMoving = bStartMoving;
	directionSign = StartDirectionSign;
	startLocation = GetActorLocation();
	translationDistance = MoveSpeed * TravelTime;
	endLocation = GetActorLocation() + MoveDirection.GetSafeNormal() * directionSign * translationDistance;

	UE_LOG(LogTemp, Display, TEXT("This display message was brought to you by %s"), *GetActorNameOrLabel());
	UE_LOG(LogTemp, Warning, TEXT("This is a warning message!"));
	UE_LOG(LogTemp, Error, TEXT("This is an error message!"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float deltaTime)
{
	FVector CurrentLocation = GetActorLocation();

	if (!bIsMoving) 
	{
		if (!TimerFinished(timer, WaitTime)) 
		{
			timer += deltaTime;
			return;
		}
		bIsMoving = true;
		timer = 0;
		return;
	}

	SetLerpLocations();
	if(!TimerFinished(timer, TravelTime))
	{
		SetActorLocation(CurrentLocation + MoveDirection.GetSafeNormal() * directionSign * MoveSpeed * deltaTime);
		timer += deltaTime;
		return;
	}
	SetActorLocation(endLocation);
	bIsMoving = false;
	directionSign = -directionSign;
	
	timer = 0;

	distanceFromStartPosition = FVector::Dist(startLocation, CurrentLocation);
}

void AMovingPlatform::SetLerpLocations()
{
	startLocation = GetActorLocation();
	endLocation = startLocation + MoveDirection.GetSafeNormal() * directionSign * TravelTime;
}

void AMovingPlatform::RotatePlatform(float deltaTime)
{
	FVector eulerRot = GetActorRotation().Euler();
	eulerRot += AddedRotationEuler * deltaTime;
	SetActorRotation(FRotator::MakeFromEuler(eulerRot));
}

bool AMovingPlatform::TimerFinished(float currentTime, float totalTime) const
{
	return !(currentTime < totalTime);
}

FVector AMovingPlatform::LerpVector(FVector from, FVector to, float delta) const
{
	float x = (from.X + (to.X - from.X) * delta);
	float y = (from.Y + (to.Y - from.Y) * delta);
	float z = (from.Z + (to.Z - from.Z) * delta);
	return FVector(x, y, z);
}
