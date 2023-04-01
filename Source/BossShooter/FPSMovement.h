// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSMovement.generated.h"

UCLASS()
class BOSSSHOOTER_API AFPSMovement : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MovementControls")
	float Speed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MovementControls")
	float JumpZVelocity;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MovementControls")
	float AirControlForce;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "MovementControls")
	float MaxSensitivity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MovementControls")
	float MouseSensitivity;



	UPROPERTY(VisibleAnywhere, Category = "CameraVariables")
	class UCameraComponent* MainCamera;
	FORCEINLINE UCameraComponent* GetCamera() { return MainCamera; }
	FORCEINLINE void SetCamera(UCameraComponent* NewCamera) { MainCamera = NewCamera; }



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DashAction")
	float MaxDashStamina;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DashAction")
	float StaminaPerDash;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DashAction")
	float CurStamina;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DashAction")
	float StaminaRecoveryPerSecond;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DashAction")
	float DashGroundForce;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "DashAction")
	float DashAirForce;


	// get damaged for Damage amount and be thrown with ThrowForce
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damaged")
	bool bLaunched;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damaged")
	float InvulnerabilityTime;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Damaged")
	float CurInvulnerabilityTime;
	UFUNCTION()
	void GetDamaged(float Damage, FVector ThrowForce = FVector::ZeroVector);


private:

	FVector ExpectedMoveDirection;
	void MoveForward(float Value);
	void MoveRight(float Value);

	void LookUp(float Value);
	void Turn(float Value);

	void DashAction();
	void JumpAction();

};
