// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArkanoidGameModeBase.generated.h"

/**
 * Main Game mode for Arkanoid
 */
UCLASS()
class ARKANOID_API AArkanoidGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AArkanoidGameModeBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Takes away the effects given from the power ups
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, Category="Power Up")
	void RevertPowerups();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Current number of active balls in the level
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Attributes")
		int BallsInLevel;
	// Total amount of blocks in the level
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Attributes")
		int AmountOfBlocks;

};
