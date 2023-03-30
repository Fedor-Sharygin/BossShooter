// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Critter.generated.h"

UCLASS()
class BOSSSHOOTER_API ACritter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACritter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UPROPERTY(EditAnywhere, Category = "Mesh")
	class USkeletalMeshComponent* MeshComponent;

	UPROPERTY(EditAnywhere, Category = "Camera")
	class UCameraComponent* Camera;

public:
	UPROPERTY(EditAnywhere, Category = "MovementVariables")
	float MaxSpeed;

	UPROPERTY(EditAnywhere, Category = "MovementVariables")
	float MouseSensitivity;

	UPROPERTY(EditDefaultsOnly, Category = "MovementVariables")
	float MaxSensitivity;

	UPROPERTY(EditAnywhere, Category = "MovementVariables")
	float LowestZVal;
	UPROPERTY(EditAnywhere, Category = "MovementVariables")
	float HighestZVal;

private:
	FVector Direction;
	FVector CurrentVelocity;

	void MoveForward(float Value);
	void MoveRight(float Value);

	void SetVelocity();


	float MaxCameraDist;
	float MaxCameraDistSq;

	void Turn(float Value);
	void LookUp(float Value);

};
