// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Collider.generated.h"

UCLASS()
class BOSSSHOOTER_API ACollider : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACollider();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* MeshComponent;
	FORCEINLINE UStaticMeshComponent* GetMeshComponent() { return MeshComponent; }
	FORCEINLINE void SetStaticMeshComponent(UStaticMeshComponent* NewMeshComponent) { MeshComponent = NewMeshComponent; }
	

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class USphereComponent* SphereComponent;
	FORCEINLINE USphereComponent* GetSphereComponent() { return SphereComponent; }
	FORCEINLINE void SetSphereComponent(USphereComponent* NewSphereComponent) { SphereComponent = NewSphereComponent; }


	UPROPERTY(VisibleAnywhere, Category = "CameraVariables")
	class UCameraComponent* Camera;
	FORCEINLINE UCameraComponent* GetCamera() { return Camera; }
	FORCEINLINE void SetCamera(UCameraComponent* NewCamera) { Camera = NewCamera; }


	UPROPERTY(VisibleAnywhere, Category = "CameraVariables")
	class USpringArmComponent* SpringArm;
	FORCEINLINE USpringArmComponent* GetSpringArm() { return SpringArm; }
	FORCEINLINE void SetSpringArm(USpringArmComponent* NewSpringArm) { SpringArm = NewSpringArm; }


	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UColliderMovementComponent* MyMovementComponent;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

private:

	void MoveForward(float Value);
	void MoveRight(float Value);

	void LookUp(float Value);
	void Turn(float Value);

	FVector2D CameraInput;

};
