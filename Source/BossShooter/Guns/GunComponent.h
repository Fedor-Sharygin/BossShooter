// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GunComponent.generated.h"


UENUM(BlueprintType)
enum class EGunType : uint8
{
	EGT_HitScan		UMETA(DisplayName = "Hit Scan"),
	EGT_Launcher	UMETA(DisplayName = "Launcher"),
	
	EGT_Max			UMETA(DisplayName = "Default")
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), ABSTRACT )
class BOSSSHOOTER_API UGunComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGunComponent();

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Gun behavior")
	EGunType GunType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun behavior")
	float DamagePerUnit;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun behavior")
	int UnitsPerShot;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun behavior")
	float CooldownTime;
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "Gun behavior")
	float CooldownTimeLeft;

	UFUNCTION(Blueprintable, Category = "Gun behavior")
	virtual void Shoot() PURE_VIRTUAL(UGunComponent::Shoot, );

		
};
