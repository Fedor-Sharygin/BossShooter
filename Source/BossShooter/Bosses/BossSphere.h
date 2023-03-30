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
	BMS_SpinArena		UMETA(DisplayName = "SpinArena"),

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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behavior")
	EBossSphereStatus HPStatus;
	FORCEINLINE void SetBossSphereStatus(EBossSphereStatus _HPStatus) { HPStatus = _HPStatus; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Behavior")
	float MaxHP;
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Behavior")
	float CurHP;

	// Movement Status
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Behavior")
	EBossMovementStatus MoveStatus;
	FORCEINLINE void SetBossMovementStatus(EBossMovementStatus _MoveStatus) { MoveStatus = _MoveStatus; }

	// Targetable peaks for movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Behavior")
	TArray<FVector> PeakPositions;

	// Spinnable Player Actor
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Behavior")
	AActor* Player;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MovementVariables")
	float PeakSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MovementVariables")
	float ToPlayerSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MovementVariables")
	float SpinSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MovementVariables")
	float CircleDist;

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

private:

	float TickTime;

	// attacking behavior
	void MoveToRandomPeak();
	void RushToPlayer();

	bool bClockwise;
	float TargetAngle;
	void CircleArena();
	void SpinAttractPlayer();

};
