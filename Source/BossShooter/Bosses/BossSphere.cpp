// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSphere.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../FPSMovement.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABossSphere::ABossSphere()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DamageSphere"));
	DamageSphere->SetupAttachment(GetRootComponent());
	DamageSphere->SetSphereRadius(350.f);
	DamageSphere->SetCollisionProfileName(TEXT("DamageSphere"));

	SphereMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMeshComponent"));
	SphereMeshComponent->SetupAttachment(GetRootComponent());

	HPStatus = EBossSphereStatus::BSS_Max;
	MoveStatus = EBossMovementStatus::BMS_Max;

	MaxHP = 500.f;

}

// Called when the game starts or when spawned
void ABossSphere::BeginPlay()
{
	Super::BeginPlay();
	
	CurHP = MaxHP;

	TTHP = 2.f * MaxHP / 3.f;
	OTHP = MaxHP / 3.f;

	Player = UGameplayStatics::GetActorOfClass(GetWorld(), AFPSMovement::StaticClass());

}

// Called every frame
void ABossSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickTime = DeltaTime;

	if (CurHP <= MaxHP && CurHP > TTHP)
	{
		HPStatus = EBossSphereStatus::BSS_FullHP;
	}
	else if (CurHP <= TTHP && CurHP > OTHP)
	{
		HPStatus = EBossSphereStatus::BSS_MedHP;
	}
	else if (CurHP <= OTHP && CurHP > 0.f)
	{
		HPStatus = EBossSphereStatus::BSS_LowHP;
	}
	else
	{
		HPStatus = EBossSphereStatus::BSS_Death;
	}

	//SpinAttractPlayer();

}

// Called to bind functionality to input
void ABossSphere::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABossSphere::MoveToRandomPeak()
{

}

void ABossSphere::RushToPlayer()
{

}

void ABossSphere::CircleArena()
{
	if (MoveStatus != EBossMovementStatus::BMS_CircleArena)
	{
		MoveStatus = EBossMovementStatus::BMS_CircleArena;
		bClockwise = FMath::RandBool();
	}

	
}

void ABossSphere::SpinAttractPlayer()
{
	if (!Player)
		return;

	FVector AttractionLocation = Player->GetActorLocation() * 0.994f;
	Player->SetActorLocation(AttractionLocation);
}

