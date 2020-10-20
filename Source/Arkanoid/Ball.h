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

	//--Ball Movement Functions--//
	UFUNCTION(BlueprintImplementableEvent, Category ="Ball Movement")
	void ClampingMovement();

public:
	//Mesh of the ball
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ball")
		class UStaticMeshComponent* BallMesh;
	//--Ball Movement Variables--//
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ball Movement")
		float SpeedMultiplier;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ball Movement")
		float DefaultSpeedMultipler;

	// For when ball is destroyed or start of a level
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Attributes")
		bool bWaitToStart;
};
