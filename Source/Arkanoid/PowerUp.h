// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"
UENUM(BlueprintType)
enum EPowerUpType
{
	SLOW			UMETA(DisplayName = "Slow PowerUp"),			// Slows down the ball
	MULTIBALL		UMETA(DisplayName = "Multiple Balls PowerUp"),	// Creates a second ball
	ENLARGE			UMETA(DisplayName = "Enlarge Vaus PowerUp"),	// Makes Vaus bigger
};

UCLASS()
class ARKANOID_API APowerUp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void ApplyPowerUpEffects(TEnumAsByte<EPowerUpType> CurrentPowerUpType, AActor* AffectedActor);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION(BlueprintImplementableEvent, Category = "PowerUp")
	void SpawnMultiBall();

	void FallingDown();
public:	
	// Power up type, selected on spawn of this object
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PowerUp")
	TEnumAsByte<EPowerUpType> PowerUpType;
	// capsule to mimic original arkanoid
	// NOTE: Capsule collision has been altered to only have XY simple collision
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerUp")
	class UStaticMeshComponent* PowerUpMesh;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "PowerUp")
		float SpeedMultiplier;

};
