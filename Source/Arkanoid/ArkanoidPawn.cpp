// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidPawn.h"
// Sets default values
AArkanoidPawn::AArkanoidPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Setup Components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Platform Mesh"));
	MeshComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Platform(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	MeshComponent->SetStaticMesh(Platform.Object);
	MeshComponent->SetRelativeScale3D(FVector(1.0f, 3.5f, 1.0f));

}

// Called when the game starts or when spawned
void AArkanoidPawn::BeginPlay()
{
	Super::BeginPlay();

	//Moving in game requires a unit per second as movement input alone is only between -1 to 1
	if (SpeedMultipler == 0.0f)
	{
		SpeedMultipler = 1000.0f;
	}
}


// Called every frame
void AArkanoidPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move(DeltaTime);
}

// Called to bind functionality to input
void AArkanoidPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent != nullptr)
	{
		PlayerInputComponent->BindAxis("MoveRight", this, &AArkanoidPawn::MoveRight);
	}
}

// Called on axis input
void AArkanoidPawn::MoveRight(float AxisValue)
{
	MovementInput = FMath::Clamp(AxisValue, -1.0f, 1.0f);
}


void AArkanoidPawn::Move(float DeltaTime)
{
	// Calculate Movement as such:
	// 1. Get current location
	// 2. Find the value of the direction vector multiplied by the movement input
	// 3. Apply the newly found direction vector to the current location vector found in step 1
	// 4. Set new location to end result value found in step 3
	if (MovementInput != 0)
	{
		FVector MoveLocation = GetActorLocation();
		MovementInput *= SpeedMultipler;
		MoveLocation += GetActorRightVector() * MovementInput * DeltaTime;
		SetActorLocation(MoveLocation);
	}

}