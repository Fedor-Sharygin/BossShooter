// Fill out your copyright notice in the Description page of Project Settings.


#include "AIBossController.h"
#include "BossSphere.h"


void AAIBossController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!InPawn)
		return;

	ABossSphere* BSPawn = Cast<ABossSphere>(InPawn);
	if (!BSPawn)
		return;

	if (BSPawn->MainBT)
		RunBehaviorTree(BSPawn->MainBT);
}

