// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BossSphere.generated.h"


UENUM(BlueprintType)
enum class EBossSphereStatus : uint8
{
	BSS_FullHP		UMETA(DisplayName = "FullHP"),
	BSS_MedHP		UMETA(DisplayName = "MedHP"),
	BSS_LowHP		UMETA(DisplayName = "LowHP"),
	BSS_Death		UMETA(DisplayName = "Death"),

	BSS_Max			UMETA(DisplayName = "Default")
};

UENUM(BlueprintType)
enum class EBossMovementStatus : uint8
{
	BMS_PeakMove		UMETA(DisplayName = "ToPeak"),
	BMS_PlayerMove		UMETA(DisplayName = "ToPlayer"),
	BMS_CircleArena		UMETA(DisplayName = "CircleArena"),
	BMS_SpinAttract		UMETA(DisplayName = "SpinAttract"),

	BMS_Max				UMETA(DisplayName = "Default")
};

UCLASS()
class BOSSSHOOTER_API ABossSphere : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABossSphere();


	// BossSphere behavior variables
	// HP status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI | Behavior")
	EBossSphereStatus HPStatus;
	FORCEINLINE void SetBossSphereStatus(EBossSphereStatus _HPStatus) { HPStatus = _HPStatus; }

	UPROPERTY(EditInstanceOnly, Category = "AI | Behavior")
	float MaxHP;
	class UBossHPComponent* HPComponent;

	// Movement Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI | Behavior")
	EBossMovementStatus MoveStatus;
	FORCEINLINE void SetBossMovementStatus(EBossMovementStatus _MoveStatus) { MoveStatus = _MoveStatus; }

	// Targetable peaks for movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Behavior")
	TArray<FVector> PeakPositions;

	// Spinnable Player Actor
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "AI | Behavior")
	class AFPSMovement* Player;

	// Attacking
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI")
	class AAIController* AIController;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	class UBehaviorTree* MainBT;

private:
	float TTHP, OTHP; // two thirds and one third hp respectively for behavior evaluation

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* SphereMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "DamageRange")
	class USphereComponent* DamageSphere;


	// damage function
	UFUNCTION()
	void OnDamageSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Attack")
	float LaunchForce;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI | Behavior | MovementVariables")
	bool bReachedDest;
	
	// attacking behavior
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Behavior | MovementVariables")
	float PeakSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Behavior | MovementVariables")
	float PeakJumpForce;
	UPROPERTY(VisibleInstanceOnly, Category = "AI | Behavior | MovementVariables")
	int PeakNum;
	UFUNCTION(BlueprintCallable, Category = "AI | Movement")
	void MoveToRandomPeak();


	UPROPERTY(VisibleInstanceOnly, Category = "AI | Behavior | MovementVariables")
	FVector ToPlayer;
	UPROPERTY(VisibleInstanceOnly, Category = "AI | Behavior | MovementVariables")
	bool bPastPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Behavior | MovementVariables")
	float ToPlayerSpeed;
	UFUNCTION(BlueprintCallable, Category = "AI | Movement")
	void RushToPlayer();


	UPROPERTY(VisibleInstanceOnly, Category = "AI | Behavior | MovementVariables")
	float TargetAngle;
	UPROPERTY(VisibleInstanceOnly, Category = "AI | Behavior | MovementVariables")
	FVector PointOnCircle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Behavior | MovementVariables")
	float CircleDist;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Behavior | MovementVariables")
	float CircleSpeed;
	UFUNCTION(BlueprintCallable, Category = "AI | Movement")
	void CircleArena();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Behavior | MovementVariables")
	float SpinSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Behavior | MovementVariables")
	float AttractionForce;
	UFUNCTION(BlueprintCallable, Category = "AI | Movement")
	void SpinAttractPlayer();

	/*UFUNCTION(BlueprintCallable, Category = "AI | Movement")
	void SetMovementStatus(EBossMovementStatus Status);*/

private:

	UCharacterMovementComponent* ThisCMC;
	float TickTime;

	bool bClockwise;

	bool MoveToPointWithSpeed(FVector Point, float Speed);
	bool MoveToPlayerWithSpeed(float Speed);



};
