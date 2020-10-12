// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ArkanoidGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ARKANOID_API UArkanoidGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UArkanoidGameInstance();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Player Attributes")
		int PlayerScore;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Attributes")
		int PlayerLives;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Player Attributes")
		int LevelsRemaining;
};
