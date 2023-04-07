// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BossHPComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOSSSHOOTER_API UBossHPComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBossHPComponent();

protected:

	virtual void BeginPlay() override;

public:	

	UPROPERTY(EditInstanceOnly, Category = "Boss HP")
	float MaxHP;
	UPROPERTY(EditInstanceOnly, Category = "Boss HP")
	float CurHP;
	
	UFUNCTION(BlueprintCallable)
	void GetDamaged(float Damage);

};
