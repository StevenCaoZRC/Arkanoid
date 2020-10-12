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
	PowerUpMesh->OnComponentHit.AddDynamic(this, &APowerUp::OnHit);
	PowerUpMesh->SetRelativeRotation(FQuat(FVector(0.0f, 90.0f, 0.0f), 1.0f));

}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	// Launching the ball at the start

	PowerUpMesh->AddImpulse(FVector(0.0f, -SpeedMultiplier, 0.0f), "NAME_None", true);
}

void APowerUp::ApplyPowerUpEffects(TEnumAsByte<EPowerUpType> CurrentPowerUpType, AActor* AffectedActor)
{
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
		TArray<AActor*> FoundBalls;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABall::StaticClass(), FoundBalls);
		for (AActor* ActorFound : FoundBalls)
		{
			ABall* BallRef = Cast<ABall>(ActorFound);
			FVector BallLocation(BallRef->GetActorLocation());
			FRotator BallRotation(0.0f, 0.0f, 0.0f);
			FVector BallScale(1.0f, 1.0f, 1.0f);
			FActorSpawnParameters BallSpawnParameters;
			 GetWorld()->SpawnActor<ABall>(BallLocation, BallRotation, BallSpawnParameters);
			//SpawnedBall->BallMesh->SetRelativeScale3D(BallScale);
			Cast<AArkanoidGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()))->BallsInLevel += 1;
		}
		break;
	}
	case ENLARGE:
	{
		// Scale Up the Player Uniformly so collision boxes scaled up also to the right size
		AArkanoidPawn* PlayerRef = Cast<AArkanoidPawn>(AffectedActor);
		FVector EnLargeScale = FVector(PlayerRef->VausMesh->GetRelativeScale3D().X , PlayerRef->VausMesh->GetRelativeScale3D().Y * 1.5f, PlayerRef->VausMesh->GetRelativeScale3D().Z);
		PlayerRef->VausMesh->SetRelativeScale3D(EnLargeScale);
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
	if ((OtherActor != nullptr) && (OtherActor != this) && !Cast<ABlock>(OtherActor))
	{
		AArkanoidPawn* PlayerRef = Cast<AArkanoidPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
		ApplyPowerUpEffects(PowerUpType, PlayerRef);
		Destroy();
	}
}

void APowerUp::FallingDown()
{
	FVector ClampedVelocity = UKismetMathLibrary::ClampVectorSize(GetVelocity(), SpeedMultiplier, SpeedMultiplier);
	PowerUpMesh->SetPhysicsLinearVelocity(ClampedVelocity);
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FallingDown();
}

