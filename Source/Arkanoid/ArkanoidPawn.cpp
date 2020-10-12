// Fill out your copyright notice in the Description page of Project Settings.


#include "ArkanoidPawn.h"
#include "Kismet/KismetMathLibrary.h"
// Sets default values
AArkanoidPawn::AArkanoidPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	VausMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Vaus"));
	VausMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Platform(TEXT("/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube"));
	VausMesh->SetStaticMesh(Platform.Object);
	VausMesh->SetRelativeScale3D(FVector(1.0f, 3.5f, 1.0f));
}

// Called when the game starts or when spawned
void AArkanoidPawn::BeginPlay()
{
	Super::BeginPlay();

	//Moving in game requires a unit per second as movement input alone is only between -1 to 1
	if (SpeedMultiplier == 0.0f)
	{
		SpeedMultiplier = 1000.0f;
	}
}


// Called every frame
void AArkanoidPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//We want the ball to be moving at the same speed constantly
	FVector ClampedVelocity = UKismetMathLibrary::ClampVectorSize(GetVelocity(), SpeedMultiplier, SpeedMultiplier);
	VausMesh->SetPhysicsLinearVelocity(ClampedVelocity);
}

// Called to bind functionality to input
void AArkanoidPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (PlayerInputComponent != nullptr)
	{
		//Handling left right movement
		PlayerInputComponent->BindAxis("MoveRight", this, &AArkanoidPawn::MoveRight);
	}
}

// Called on axis input
void AArkanoidPawn::MoveRight(float AxisValue)
{
	if (AxisValue != 0.0f)
	{
		VausMesh->AddImpulse(FVector(-AxisValue * SpeedMultiplier, 0.0f, 0.0f), "NAME_None", true);
	}
}
