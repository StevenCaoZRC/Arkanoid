// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"
#include "Ball.h"
#include "ArkanoidPawn.h"
#include "ArkanoidGameModeBase.h"
#include "Block.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	PowerUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Power Up Mesh"));
	RootComponent = PowerUpMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Capsule(TEXT("/Game/StarterContent/Shapes/Shape_NarrowCapsule.Shape_NarrowCapsule"));
	PowerUpMesh->SetStaticMesh(Capsule.Object);

	PowerUpMesh->SetRelativeRotation(FQuat(FVector(0.0f, 90.0f, 0.0f), 1.0f));
	PowerUpMesh->SetSimulatePhysics(true);
	PowerUpMesh->SetRelativeScale3D(FVector(1.5f,1.5,1.0f));
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	// Launching the ball at the start
	PowerUpMesh->OnComponentHit.AddDynamic(this, &APowerUp::OnHit);
	PowerUpMesh->AddImpulse(FVector(0.0f, -SpeedMultiplier, 0.0f), "NAME_None", true);
}

void APowerUp::ApplyPowerUpEffects(TEnumAsByte<EPowerUpType> CurrentPowerUpType, AActor* AffectedActor)
{
	/*Sets up power up effects
	* SLOW - Slowing the ball speed
	* MULTIBALL - Two balls in game
	* ENLARGE - Larger Player Platform
	*/
	//NOTE: this is determined by the CurrentPowerupType which is set on spawn of the power up and is randomized.
	switch (CurrentPowerUpType)
	{
	case SLOW:
	{
		// Decrease the speed of the ball until power up ends
		TArray<AActor*> FoundBalls;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), FoundBalls);
		for (AActor* ActorFound : FoundBalls)
		{
			ABall* BallRef = Cast<ABall>(ActorFound);
			BallRef->SpeedMultiplier *= 0.5;
		}
		break;
	}
	case MULTIBALL:
	{
		// Add a extra ball at the current balls location
		// Update Game mode with new amount of balls in level
		// Calls Blueprint implementable function
		SpawnMultiBall();
		break;
	}
	case ENLARGE:
	{
		// Scale Up the Player Uniformly so collision boxes scaled up also to the right size
		AArkanoidPawn* PlayerRef = Cast<AArkanoidPawn>(AffectedActor);
		PlayerRef->SetSizeForPowerUp();
		break;
	}
	default:
	{
		UE_LOG(LogTemp, Warning, TEXT("PowerUp.cpp : Could not identify Power Up Type"))
		break;
	}
	}
}

void APowerUp::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != nullptr) && (OtherActor != this) )
	{
		// Apply affects of powers to the player
		AArkanoidPawn* PlayerRef = Cast<AArkanoidPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		if (PlayerRef != nullptr)
		{
			ApplyPowerUpEffects(PowerUpType, PlayerRef);
		}
		Destroy();
	}
}

void APowerUp::FallingDown()
{
	// Travels down at a cosntant speed
	FVector ClampedVelocity = UKismetMathLibrary::ClampVectorSize(GetVelocity(), SpeedMultiplier, SpeedMultiplier);
	PowerUpMesh->SetPhysicsLinearVelocity(ClampedVelocity);
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FallingDown();
}

