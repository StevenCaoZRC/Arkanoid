// Copyright Epic Games, Inc. All Rights Reserved.


#include "ArkanoidGameModeBase.h"

AArkanoidGameModeBase::AArkanoidGameModeBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Components 
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	// Setup Variables
	BallsInLevel = 1;

}

// Called when the game starts or when spawned
void AArkanoidGameModeBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AArkanoidGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



