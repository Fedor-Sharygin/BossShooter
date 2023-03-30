// Fill out your copyright notice in the Description page of Project Settings.


#include "Critter.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"

// Sets default values
ACritter::ACritter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));

	MeshComponent->SetupAttachment(GetRootComponent());

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());
	Camera->SetRelativeLocation(FVector(-300.0f, 0.f, 300.f));
	Camera->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	LowestZVal = 0.f;
	HighestZVal = 1.f;
	MaxCameraDist = Camera->GetRelativeLocation().Size();
	MaxCameraDistSq = Camera->GetRelativeLocation().SizeSquared();

	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	MaxSpeed = 100.f;
	CurrentVelocity = FVector(0.f);
	Direction = FVector(0.f);

	MouseSensitivity = 80.f;
	MaxSensitivity = 160.0f;

}

// Called when the game starts or when spawned
void ACritter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACritter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetVelocity();
	FVector NewLoc = GetActorLocation() + CurrentVelocity * DeltaTime;
	SetActorLocation(NewLoc);

}

// Called to bind functionality to input
void ACritter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ACritter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ACritter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ACritter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ACritter::LookUp);

}


void ACritter::MoveForward(float Value)
{
	Direction.Y = FMath::Clamp(Value, -1.f, 1.f);
}

void ACritter::MoveRight(float Value)
{
	Direction.X = FMath::Clamp(Value, -1.f, 1.f);
}

void ACritter::SetVelocity()
{
	USceneComponent* DirectionRef = GetRootComponent();
	CurrentVelocity = Direction.Y * DirectionRef->GetForwardVector() + Direction.X * DirectionRef->GetRightVector();
	CurrentVelocity.Normalize();
	CurrentVelocity *= MaxSpeed;
}


void ACritter::Turn(float Value)
{
	GetRootComponent()->AddLocalRotation(FRotator(0.f, Value * MouseSensitivity / MaxSensitivity, 0.f));
}

void ACritter::LookUp(float Value)
{
	FRotator CameraRotation = Camera->GetRelativeRotation();
	UE_LOG(LogTemp, Warning, TEXT("Prev pitch = %f"), Camera->GetRelativeRotation().Pitch);

	CameraRotation.Yaw = CameraRotation.Roll = 0.f;
	CameraRotation.Pitch = FMath::Clamp(CameraRotation.Pitch - Value * MouseSensitivity / MaxSensitivity, FMath::Asin(-HighestZVal) / PI * 180.f, FMath::Asin(-LowestZVal) / PI * 180.f);

	Camera->SetRelativeLocation(FVector(-FMath::Cos(CameraRotation.Pitch / 180.f * PI), 0.f, -FMath::Sin(CameraRotation.Pitch / 180.f * PI)) * MaxCameraDist);
	Camera->SetRelativeRotation(CameraRotation);

	UE_LOG(LogTemp, Warning, TEXT("Prev pitch = %f"), Camera->GetRelativeRotation().Pitch);
}
