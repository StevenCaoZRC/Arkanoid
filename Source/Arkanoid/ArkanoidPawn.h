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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Movement Variables
	// Only using float as player just needs to travel left and right. (Normally it should be a FVector2D for forward and backward movement)
	float MovementInput;
	// Speed multipler applyed to axis input 
	UPROPERTY(EditDefaultsOnly, Category ="Player Movement")
	float SpeedMultipler;

	// Movement Functions
	void MoveRight(float AxisValue);
	void Move(float DeltaTime);

	UPROPERTY(EditDefaultsOnly, Category = "Player Mesh")
	class UStaticMeshComponent* MeshComponent;

};
