// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIBossController.generated.h"

/**
 * 
 */
UCLASS()
class BOSSSHOOTER_API AAIBossController : public AAIController
{
	GENERATED_BODY()

protected:
	virtual void OnPossess(APawn* InPawn) override;

};
