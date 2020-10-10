// Fill out your copyright notice in the Description page of Project Settings.


#include "Ball.h"

// Sets default values
ABall::ABall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup Components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	BallMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball"));
	BallMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));
	BallMesh->SetStaticMesh(Sphere.Object);

	// Ball PhysicsSetup
	BallMesh->SetSimulatePhysics(true);
	BallMesh->SetLinearDamping(0.0f);

	// Inital Variables
	BounceAngle = 45.0f;
}

// Called when the game starts or when spawned
void ABall::BeginPlay()
{
	Super::BeginPlay();
	
	//Making sure the ball is not stationary
	if (SpeedMultipler == 0.0f)
	{
		SpeedMultipler = 1000.0f;
	}
	
	// Get the ball moving as it is stationary at the beginning
	if (IsRootComponentMovable())
	{
		BallMesh->AddImpulse(FVector(0.0f, -SpeedMultipler, 0.0f), "NAME_None", true);
	}
}

void ABall::ClampingMovement()
{
	float ClampedVelocity = FMath::Clamp(GetVelocity().Size(), SpeedMultipler, SpeedMultipler);
	//TODO: Rotate and set linear physics velocity
		
}

// Called every frame
void ABall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ClampingMovement();
}

