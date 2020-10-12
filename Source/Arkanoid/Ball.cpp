// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"
#include "Kismet/KismetMathLibrary.h"
#include "ArkanoidPawn.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Components
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	RootComponent = BallMesh;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	BallMesh->SetStaticMesh(Sphere.Object);
	BallMesh->SetRelativeScale3D(FVector(0.7f));

	// Finding the white glowing material for the ball
	static ConstructorHelpers::FObjectFinder<UMaterialInstance> WhiteMaterial(TEXT("/Game/Materials/Material_Instances/MI_BlockWhite.MI_BlockWhite"));
	BallMesh->SetMaterial(0, WhiteMaterial.Object);

	// Ball PhysicsSetup
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetLinearDamping(0.0f);

	// Setup Variables
	DefaultSpeedMultipler = 2000.0f;
	SpeedMultiplier = DefaultSpeedMultipler;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	//Making sure the ball is not stationary
	if (SpeedMultiplier == 0.0f)
	{
		SpeedMultiplier = 2000.0f;
	}
	
	// Launching the ball at the start
	if (IsRootComponentMovable())
	{
		BallMesh->AddImpulse(FVector(0.0f, -SpeedMultiplier, 0.0f), "NAME_None", true);
	}
}

void ABall::ClampingMovement()
{
	//We want the ball to be moving at the same speed constantly
	FVector ClampedVelocity = UKismetMathLibrary::ClampVectorSize(GetVelocity(), SpeedMultiplier, SpeedMultiplier);
	BallMesh->SetPhysicsLinearVelocity(ClampedVelocity);
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ClampingMovement();
}

