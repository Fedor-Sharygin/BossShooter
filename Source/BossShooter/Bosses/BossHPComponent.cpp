// Fill out your copyright notice in the Description page of Project Settings.


#include "BossHPComponent.h"

// Sets default values for this component's properties
UBossHPComponent::UBossHPComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UBossHPComponent::BeginPlay()
{
	CurHP = MaxHP;
}

void UBossHPComponent::GetDamaged(float Damage)
{
	CurHP -= Damage;
}

