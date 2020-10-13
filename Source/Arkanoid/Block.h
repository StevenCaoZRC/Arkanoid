// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Block.generated.h"

/*
Different types of blocks in Arkanoid according to https://primetimeamusements.com/getting-good-arkanoid/#:~:text=Arkanoid%20is%20played%20entirely%20by,counterclockwise%20in%20the%20arcade%20version
 */
UENUM(BlueprintType)
enum EBlockType
{
	WHITE		UMETA(DisplayName = "White"),
	ORANGE		UMETA(DisplayName = "Orange"),
	CYAN		UMETA(DisplayName = "Cyan"),
	GREEN		UMETA(DisplayName = "Green"),
	RED			UMETA(DisplayName = "Red"),
	BLUE		UMETA(DisplayName = "Blue"),
	MAGENTA		UMETA(DisplayName = "Magenta"),
	YELLOW		UMETA(DisplayName = "Yellow"),
};

UCLASS()
class ARKANOID_API ABlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlock();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Initialises: Material, Health, Points this block is worth depending on its BlockType
	UFUNCTION()
		void InitialiseBlockAttributes(EBlockType BlockType);

	UFUNCTION(BlueprintImplementableEvent, Category="Block Power Up")
	void SpawnPowerUp();

public:	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Block")
		class UStaticMeshComponent* BlockMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Block")
		class UBoxComponent* BoxCollider;
	 
#pragma region Block Attributes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Block Attributes")
		TEnumAsByte<EBlockType> CurrentBlockType;

	UPROPERTY(BlueprintReadOnly, Category = "Block Attributes")
		int BlockHealth;

	UPROPERTY(BlueprintReadOnly, Category = "Block Attributes")
		int Points;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Block Attributes")
		class UMaterialInstance* WhiteMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Block Attributes")
		class UMaterialInstance* OrangeMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Block Attributes")
		class UMaterialInstance* CyanMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Block Attributes")
		class UMaterialInstance* GreenMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Block Attributes")
		class UMaterialInstance* RedMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Block Attributes")
		class UMaterialInstance* BlueMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Block Attributes")
		class UMaterialInstance* MagentaMaterial;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Block Attributes")
		class UMaterialInstance* YellowMaterial;
#pragma endregion // Containing Block type, Material, Health and Points Variables

	// Determines if this block can spawn a power up after being destroyed
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "BlockAttributes")
	bool bCanSpawnPowerups;
private:
	class UArkanoidGameInstance* GameInstanceRef;
};
