// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ArkanoidGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class ARKANOID_API AArkanoidGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AArkanoidGameModeBase();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable, Category="Power Up")
	void RevertPowerups();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Attributes")
		int BallsInLevel;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game Attributes")
		int AmountOfBlocks;

};
