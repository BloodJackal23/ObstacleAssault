// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	bIsMoving = bStartMoving;
	directionSign = StartDirectionSign;
	startLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector CurrentLocation = GetActorLocation();
	if(bIsMoving)
	{
		bIsMoving = !TimerFinished(TravelTime, DeltaTime);
		SetActorLocation(CurrentLocation + MoveDirection.GetSafeNormal() * directionSign * MoveSpeed * DeltaTime);
		if(!bIsMoving)
			directionSign = -directionSign;
	}
	else
	{
		bIsMoving = TimerFinished(TravelTime, DeltaTime);
	}
	DistanceFromStartPosition = FVector::Dist(startLocation, CurrentLocation);
}

bool AMovingPlatform::TimerFinished(float totalTime, float deltaTime)
{
    if(timer < totalTime)
	{
		timer += deltaTime;
		return false;
	}
	timer = 0;
	return true;
}
