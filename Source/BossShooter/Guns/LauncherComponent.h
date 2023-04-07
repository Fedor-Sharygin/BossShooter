// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GunComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LauncherComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOSSSHOOTER_API ULauncherComponent : public UGunComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULauncherComponent();

protected:

public:	

	virtual void Shoot() override;

	void SpawnProjectile();
		
};
