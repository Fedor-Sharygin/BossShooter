// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GunComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HitScanComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOSSSHOOTER_API UHitScanComponent : public UGunComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHitScanComponent();

protected:

public:	

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gun behavior | Hitscan parameters")
	bool bMouseHold;


	// camera is used to calculate the muzzle position
	// for raycasting against enemy bosses
	class UCameraComponent* ParentCamera;
	UPROPERTY(EditDefaultsOnly, Category = "Gun behavior | Hitscan parameters")
	float MuzzleOffset;
	UPROPERTY(EditDefaultsOnly, Category = "Gun behavior | Hitscan parameters")
	float ShotRange;
	UPROPERTY(EditDefaultsOnly, Category = "Gun behavior | Hitscan parameters")
	float ShotDeviation;

	virtual void Shoot() override;
	
	void Hitscan(FVector Origin, FVector RangeEnd);
	
};
