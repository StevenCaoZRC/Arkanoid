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

	// UPsiziing player when the power up is enlarge
	UFUNCTION(BlueprintImplementableEvent, Category	= "Player PowerUp")
	void SetSizeForPowerUp();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//--Movement Function--//
	void MoveRight(float AxisValue);
	void ClampVelocity();

public:
	// Mesh of the Player's platform
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Mesh")
		class UStaticMeshComponent* VausMesh;
	
	// Only One Power up can be spawned and used by the player at a time
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Attributes")
	bool bHasPowerUp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Attributes")
	FVector DefaultSize;
	// Speed multiplier applied to axis input 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Attributes")
		float SpeedMultiplier;
};
