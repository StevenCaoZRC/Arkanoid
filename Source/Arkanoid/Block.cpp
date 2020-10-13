// Fill out your copyright notice in the Description page of Project Settings.


#include "Block.h"
#include "Ball.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialInstance.h"
#include "ArkanoidGameInstance.h"
#include "ArkanoidGameModeBase.h"
#include "ArkanoidPawn.h"
#include "PowerUp.h"

// Sets default values
ABlock::ABlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Components
	BlockMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Block"));
	RootComponent = BlockMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Block(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	BlockMesh->SetStaticMesh(Block.Object);
	BlockMesh->SetRelativeScale3D(FVector(1.8f, 1.0f, 1.0f));
	BlockMesh->SetGenerateOverlapEvents(true);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(RootComponent);
	BoxCollider->SetRelativeScale3D(FVector(1.0f));
	BoxCollider->InitBoxExtent(FVector(60.0f));
	BoxCollider->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f));
	BoxCollider->SetGenerateOverlapEvents(true);

	// NOTE: Need this for collsion logic to work! & Must create this before creating blueprint child of this class else it will not work in the constructor.
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ABlock::OnOverlapEnd);

	WhiteMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("White Material"));
	OrangeMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("Orange Material"));
	CyanMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("Cyan Material"));
	GreenMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("Green Material"));
	RedMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("Red Material"));
	BlueMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("Blue Material"));
	MagentaMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("Magenta Material"));
	YellowMaterial = CreateDefaultSubobject<UMaterialInstance>(TEXT("Yellow Material"));

	//Setup Variables
	bCanSpawnPowerups = false;
}

// Called when the game starts or when spawned
void ABlock::BeginPlay()
{
	Super::BeginPlay();
	InitialiseBlockAttributes(CurrentBlockType);
}

void ABlock::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	/* On overlaping with a ball we want to do as such:
	* Step1: Decreased the health of this current block
	* Step2: Check process done in step 1 takes the total hp of the block to less then 0
	* Step3: If Step 2 was successful, we want to award the player points and check if this block can spawn a power up (skip this step if step 2 was false)
	* Step4: Delete this object
	*/
	if ((OtherActor!= nullptr) && (OtherActor != this))
	{
		//Modify Score
		BlockHealth -= 1;
		if (BlockHealth <= 0)
		{
			GameInstanceRef = Cast<UArkanoidGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
			GameInstanceRef->PlayerScore += Points;
			Cast<AArkanoidGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->AmountOfBlocks -= 1;
			AArkanoidPawn* PlayerRef = Cast<AArkanoidPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			if (PlayerRef->bHasPowerUp == false)
			{
				// A Blueprint implemented function
				// Checks if the current block can spawn a power up and spawns a power if the bool is true
				SpawnPowerUp();
				PlayerRef->bHasPowerUp = true;
			}
			Destroy();
		}
	}
	
}

void ABlock::InitialiseBlockAttributes(EBlockType BlockType)
{
	/*Setting blocks attributes:
	* Material
	* Points the blocks are worth
	* Health of the block
	*/
	//NOTE: this way we can easily change these attributes just by changing the block type of this block in editor
	switch (BlockType)
	{
	case WHITE:
	{
		if (WhiteMaterial != nullptr)
		{
			BlockMesh->SetMaterial(0, WhiteMaterial);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Block.cpp : White Material Missing"));
		}
		BlockHealth = 1;
		Points = 50;
		break;
	}
	case ORANGE:
	{
		if (OrangeMaterial)
		{
			BlockMesh->SetMaterial(0, OrangeMaterial);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Block.cpp : Orange Material Missing"));
		}
		BlockHealth = 1;
		Points = 60;
		break;
	}
	case CYAN:
	{
		if (CyanMaterial)
		{
			BlockMesh->SetMaterial(0, CyanMaterial);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Block.cpp : Cyan Material Missing"));
		}
		BlockHealth = 1;
		Points = 70;
		break;
	}
	case GREEN:
	{
		if (GreenMaterial)
		{
			BlockMesh->SetMaterial(0, GreenMaterial);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Block.cpp : Green Material Missing"));
		}
		BlockHealth = 2;
		Points = 80;
		break;
	}
	case RED:
	{
		if (RedMaterial)
		{
			BlockMesh->SetMaterial(0, RedMaterial);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Block.cpp : Red Material Missing"));
		}
		BlockHealth = 2;
		Points = 90;
		break;
	}
	case BLUE:
	{
		if (BlueMaterial)
		{
			BlockMesh->SetMaterial(0, BlueMaterial);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Block.cpp : Blue Material Missing"));
		}
		BlockHealth = 2;
		Points = 100;
		break;
	}
	case MAGENTA:
	{
		if (MagentaMaterial)
		{
			BlockMesh->SetMaterial(0, MagentaMaterial);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Block.cpp : Magenta Material Missing"));
		}
		BlockHealth = 3;
		Points = 110;
		break;
	}
	case YELLOW:
	{
		if (YellowMaterial)
		{
			BlockMesh->SetMaterial(0, YellowMaterial);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Block.cpp : Yellow Material Missing"));
		}
		BlockHealth = 3;
		Points = 120;
		break;
	}
	default:
	{
		UE_LOG(LogTemp, Warning, TEXT("Block.cpp : Could not find correct blocktype to setup material and points"))
		break;
	}
	}
}

// Called every frame
void ABlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

