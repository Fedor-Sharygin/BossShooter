// Fill out your copyright notice in the Description page of Project Settings.


#include "LauncherComponent.h"

// Sets default values for this component's properties
ULauncherComponent::ULauncherComponent()
	:
UGunComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	GunType = EGunType::EGT_Launcher;
}


void ULauncherComponent::Shoot()
{
	// do not shoot unless off cooldown
	if (CooldownTimeLeft < CooldownTime)
		return;


}

void ULauncherComponent::SpawnProjectile()
{

}
