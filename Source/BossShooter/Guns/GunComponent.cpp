// Fill out your copyright notice in the Description page of Project Settings.


#include "GunComponent.h"

// Sets default values for this component's properties
UGunComponent::UGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	GunType = EGunType::EGT_Max;
}

void UGunComponent::BeginPlay()
{
	CooldownTimeLeft = CooldownTime;
}

void UGunComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CooldownTimeLeft < CooldownTime)
	{
		CooldownTimeLeft += DeltaTime;
	}
}




