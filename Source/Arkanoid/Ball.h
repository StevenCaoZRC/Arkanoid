// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ball.generated.h"

UCLASS()
class ARKANOID_API ABall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABall();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//--Ball Movement Variables--//
	UPROPERTY(EditDefaultsOnly, Category = "Ball Movement")
	float SpeedMultipler;
	float BounceAngle;
	
	//--Ball Movement Functions--//
	void ClampingMovement();

	//Mesh of the ball
	UPROPERTY(EditDefaultsOnly, Category = "Ball Mesh")
	class UStaticMeshComponent* BallMesh;
};
