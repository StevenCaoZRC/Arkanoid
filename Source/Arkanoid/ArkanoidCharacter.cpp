// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidCharacter.h"

// Sets default values
AArkanoidCharacter::AArkanoidCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AArkanoidCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArkanoidCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AArkanoidCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

