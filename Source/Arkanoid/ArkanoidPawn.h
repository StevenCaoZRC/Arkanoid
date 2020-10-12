// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ArkanoidPawn.generated.h"

UCLASS()
class ARKANOID_API AArkanoidPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AArkanoidPawn();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Mesh of the Player's platform
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Mesh")
		class UStaticMeshComponent* VausMesh;
	FVector DefaultPawnSize;

	// Only One Power up can be spawned and used by the player at a time
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Attributes")
	bool bHasPowerUp;

	// Speed multiplier applied to axis input 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Attributes")
		float SpeedMultiplier;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	//--Movement Function--//
	void MoveRight(float AxisValue);
protected: 
	float MovementDeltaTime;
};
