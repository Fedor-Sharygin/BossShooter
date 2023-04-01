// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSMovement.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFPSMovement::AFPSMovement()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 800.f;
	JumpZVelocity = 500.f;
	AirControlForce = .7f;

	MainCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("MainCamera"));
	MainCamera->SetupAttachment(GetRootComponent());
	MainCamera->SetRelativeLocation(FVector(-10.f, 0.f, 50.f));

	CurStamina = MaxDashStamina = 200.f;
	StaminaPerDash = 100.0f;
	StaminaRecoveryPerSecond = 40.f;
	DashAirForce = 900.f;
	DashGroundForce = 1500.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	CurInvulnerabilityTime = InvulnerabilityTime = 2.f;

}

// Called when the game starts or when spawned
void AFPSMovement::BeginPlay()
{
	Super::BeginPlay();
	
	UCharacterMovementComponent* ThisCMC = Cast<UCharacterMovementComponent>(GetMovementComponent());
	ThisCMC->MaxWalkSpeed = Speed;
	ThisCMC->JumpZVelocity = JumpZVelocity;
	ThisCMC->AirControl = AirControlForce;

}

// Called every frame
void AFPSMovement::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurStamina < MaxDashStamina)
	{
		CurStamina = FMath::Clamp(CurStamina + DeltaTime * StaminaRecoveryPerSecond, 0.f, MaxDashStamina);
	}
	ExpectedMoveDirection = FVector::ZeroVector;

	if (CurInvulnerabilityTime < InvulnerabilityTime)
	{
		CurInvulnerabilityTime += DeltaTime;
	}
}

// Called to bind functionality to input
void AFPSMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AFPSMovement::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AFPSMovement::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &AFPSMovement::LookUp);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &AFPSMovement::Turn);

	PlayerInputComponent->BindAction(TEXT("Dash"), EInputEvent::IE_Pressed, this, &AFPSMovement::DashAction);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &AFPSMovement::JumpAction);

}


void AFPSMovement::GetDamaged(float Damage, FVector ThrowForce)
{
	/** add damage to health later*/

	if (CurInvulnerabilityTime >= InvulnerabilityTime && !ThrowForce.IsNearlyZero())
	{
		LaunchCharacter(ThrowForce, true, false);
		CurInvulnerabilityTime = 0.f;
	}
}



void AFPSMovement::MoveForward(float Value)
{
	FVector Forward = GetActorForwardVector();
	ExpectedMoveDirection += Forward;
	if (Controller != nullptr && Value != 0.f)
	{
		AddMovementInput(Value * Forward);
	}
}

void AFPSMovement::MoveRight(float Value)
{
	FVector Right = GetActorRightVector();
	ExpectedMoveDirection += Right;
	if (Controller != nullptr && Value != 0.f)
	{
		AddMovementInput(Value * Right);
	}
}

void AFPSMovement::LookUp(float Value)
{
	FRotator PitchRotation = FRotator(Value * MouseSensitivity / MaxSensitivity, 0.f, 0.f);
	FRotator NewRotation = MainCamera->GetComponentRotation() - PitchRotation;
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch, -80.f, 80.f);
	MainCamera->SetWorldRotation(NewRotation);
}

void AFPSMovement::Turn(float Value)
{
	//FRotator TurnRotation = FRotator(0.f, Value * MouseSensitivity / MaxSensitivity, 0.f);
	if (Controller != nullptr && Value != 0.f)
	{
		AddControllerYawInput(Value * MouseSensitivity / MaxSensitivity);
	}
}


void AFPSMovement::DashAction()
{
	if (CurStamina < StaminaPerDash)
		return;

	CurStamina = FMath::Clamp(CurStamina - StaminaPerDash, 0.f, StaminaPerDash);
	float DashForce = DashAirForce;
	if (GetMovementComponent()->IsMovingOnGround())
	{
		DashForce = DashGroundForce;
	}
	
	FVector DashDir = GetMovementComponent()->GetLastInputVector();
	if (DashDir.IsNearlyZero())
		DashDir = GetActorForwardVector();
	DashDir.Normalize();
	LaunchCharacter(DashForce * DashDir, true, false);

}

void AFPSMovement::JumpAction()
{
	if (GetMovementComponent()->IsMovingOnGround())
	{
		Jump();
	}
}

