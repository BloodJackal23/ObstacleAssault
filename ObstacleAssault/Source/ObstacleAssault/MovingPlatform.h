// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Math/Vector.h"
#include "MovingPlatform.generated.h"

UCLASS()
class OBSTACLEASSAULT_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	FVector MoveDirection = FVector(0, 1, 0);

	UPROPERTY(EditAnywhere)
	float MoveSpeed = 3.0f;

	UPROPERTY(EditAnywhere)
	float TravelTime = 3.0f;

	UPROPERTY(EditAnywhere)
	float WaitTime = 1.5f;

	UPROPERTY(EditAnywhere)
	bool bStartMoving = true;

	UPROPERTY(VisibleAnywhere, Category = "Debug")
	float DistanceFromStartPosition;

private:
	bool bIsMoving = false;
	int32 DirectionSign = 1;
	float timer = 0.0f;

	bool TimerFinished(float totalTime, float deltaTime);

	FVector startLocation;
};
