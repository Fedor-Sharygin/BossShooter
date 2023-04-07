// Fill out your copyright notice in the Description page of Project Settings.


#include "HitScanComponent.h"
#include "../Bosses/BossHPComponent.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"

// Sets default values for this component's properties
UHitScanComponent::UHitScanComponent()
	:
UGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	GunType = EGunType::EGT_HitScan;
}



void UHitScanComponent::Shoot()
{
	FVector CameraDirection = ParentCamera->GetForwardVector();
	FVector MuzzleOrigin = ParentCamera->GetComponentLocation() + CameraDirection * MuzzleOffset;
	for (int i = 0; i < UnitsPerShot; ++i)
	{
		float RandomAngle = FMath::RandRange(0.f, 360.f);
		float RASin, RACos;
		FMath::SinCos(&RASin, &RACos, RandomAngle);
		FVector RandomDeviation = ParentCamera->GetUpVector() * RACos + ParentCamera->GetRightVector() * RASin;

		FVector ShotEndDir = CameraDirection + ShotDeviation * RandomDeviation;
		ShotEndDir.Normalize();

		FVector ShotEnd = MuzzleOrigin + ShotRange * ShotEndDir;

		Hitscan(MuzzleOrigin, ShotEnd);
	}
}


void UHitScanComponent::Hitscan(FVector Origin, FVector RangeEnd)
{
	FHitResult HitRes;
	bool bResult = GetWorld()->LineTraceSingleByChannel(HitRes, Origin, RangeEnd, ECC_Pawn);

	AActor* HitObject = HitRes.GetActor();

	if (bResult && HitObject)
	{

	}
}

