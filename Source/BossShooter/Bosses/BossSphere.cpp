// Fill out your copyright notice in the Description page of Project Settings.


#include "BossSphere.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../FPSMovement.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AIBossSphereController.h"
#include "BehaviorTree/BehaviorTree.h"

// Sets default values
ABossSphere::ABossSphere()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DamageSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DamageSphere"));
	DamageSphere->SetupAttachment(GetRootComponent());
	DamageSphere->SetSphereRadius(350.f);
	DamageSphere->SetCollisionProfileName(TEXT("DamageSphere"));

	DamageSphere->OnComponentBeginOverlap.AddDynamic(this, &ABossSphere::OnDamageSphereBeginOverlap);

	SphereMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SphereMeshComponent"));
	SphereMeshComponent->SetupAttachment(GetRootComponent());

	LaunchForce = 4000.f;

	HPStatus = EBossSphereStatus::BSS_Max;
	MoveStatus = EBossMovementStatus::BMS_Max;

	MaxHP = 500.f;

	CircleDist = 2000.f;
	CircleSpeed = 1200.f;

	PeakJumpForce = 800.f;
	PeakNum = -1;

	bPastPlayer = false;

}

// Called when the game starts or when spawned
void ABossSphere::BeginPlay()
{
	Super::BeginPlay();

	AIController = Cast<AAIController>(GetController());
	
	CurHP = MaxHP;

	TTHP = 2.f * MaxHP / 3.f;
	OTHP = MaxHP / 3.f;

	Player = Cast<AFPSMovement>(UGameplayStatics::GetActorOfClass(GetWorld(), AFPSMovement::StaticClass()));

	ThisCMC = Cast<UCharacterMovementComponent>(GetMovementComponent());

	bReachedDest = false;

}

// Called every frame
void ABossSphere::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TickTime = DeltaTime;

	if (!AIController)
		return;

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
	//CircleArena();

	/*if (ThisCMC->IsMovingOnGround())
	{
		Jump();
		ThisCMC->JumpZVelocity += 50.f;
	}*/

	//MoveToRandomPeak();
	//RushToPlayer();

}

// Called to bind functionality to input
void ABossSphere::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABossSphere::MoveToRandomPeak()
{
	//if (MoveStatus != EBossMovementStatus::BMS_PeakMove)
		//MoveStatus = EBossMovementStatus::BMS_PeakMove;

	bReachedDest = false;
	if (PeakNum != -1)
	{
		// reached the peak
		if (!MoveToPointWithSpeed(PeakPositions[PeakNum], PeakSpeed))
		{
			bReachedDest = true;
			ThisCMC->JumpZVelocity = PeakJumpForce;
			Jump();
			PeakNum = -1;
			MoveStatus = EBossMovementStatus::BMS_PlayerMove;
		}
		return;
	}

	PeakNum = FMath::RandRange(0, PeakPositions.Num()-1);
	UE_LOG(LogTemp, Warning, TEXT("PeakNum = %d"), PeakNum);
}

void ABossSphere::RushToPlayer()
{
	//if (MoveStatus != EBossMovementStatus::BMS_PlayerMove)
		//MoveStatus = EBossMovementStatus::BMS_PlayerMove;

	bReachedDest = false;
	MoveToPlayerWithSpeed(ToPlayerSpeed);
}

/*void ABossSphere::SetMovementStatus(EBossMovementStatus Status)
{
	SetBossMovementStatus(Status);
	if (Status == EBossMovementStatus::BMS_CircleArena)
	{
		bClockwise = FMath::RandBool();
	}
}*/

void ABossSphere::CircleArena()
{
	/*if (MoveStatus != EBossMovementStatus::BMS_CircleArena)
	{
		MoveStatus = EBossMovementStatus::BMS_CircleArena;
		bClockwise = FMath::RandBool();
	}*/

	bReachedDest = false;
	if (!PointOnCircle.IsNearlyZero() && MoveToPointWithSpeed(PointOnCircle, CircleSpeed))
	{
		bReachedDest = true;
		return;
	}

	float SinCoord = 0.f, CosCoord = 0.f;
	FMath::SinCos(&SinCoord, &CosCoord, TargetAngle * PI / 180.f);
	PointOnCircle = FVector(SinCoord, CosCoord, 0.f) * CircleDist;
	PointOnCircle.Z = 300.f;
	TargetAngle += 180.f / 4.f * (bClockwise ? -1.f : 1.f);
}

void ABossSphere::SpinAttractPlayer()
{
	//if (MoveStatus != EBossMovementStatus::BMS_SpinAttract)
		//MoveStatus = EBossMovementStatus::BMS_SpinAttract;

	if (!Player)
		return;

	FVector PLLoc = Player->GetActorLocation();
	FVector AttractionLocation = PLLoc - (PLLoc - GetActorLocation()) * (1 - AttractionForce);
	Player->SetActorLocation(AttractionLocation);

	SphereMeshComponent->AddLocalRotation(FRotator(0.f, SpinSpeed * TickTime, 0.f));
}


void ABossSphere::OnDamageSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapping with Actor"));
	if (OtherActor && Player == Cast<AFPSMovement>(OtherActor))
	{
		FVector LaunchVector = Player->GetActorLocation() - GetActorLocation();
		LaunchVector.Normalize();
		LaunchVector.Z *= -1.f;

		UE_LOG(LogTemp, Warning, TEXT("Launch in the direction: %f, %f, %f"), LaunchVector.X, LaunchVector.Y, LaunchVector.Z);

		Player->GetDamaged(10.f, LaunchVector * LaunchForce);
	}
}



bool ABossSphere::MoveToPointWithSpeed(FVector Point, float Speed)
{
	if (ThisCMC)
		ThisCMC->MaxWalkSpeed = Speed;

	if (FVector::Dist2D(GetActorLocation(), Point) < 510.f)
		return false;

	FAIMoveRequest AIMoveReq(Point);
	AIMoveReq.SetAllowPartialPath(true);
	AIController->MoveTo(AIMoveReq);

	return true;
}

bool ABossSphere::MoveToPlayerWithSpeed(float Speed)
{
	if (ThisCMC)
		ThisCMC->MaxWalkSpeed = Speed;

	if(bPastPlayer)
	{
		if (ToPlayer.IsNearlyZero())
		{
			ToPlayer = GetActorLocation() + (Player->GetActorLocation() - GetActorLocation()) * 2.f;
			ToPlayer.Z = 0.f;

			if (ToPlayer.Size() > 1500.f)
			{
				ToPlayer.Normalize();
				ToPlayer *= 1500.f;
			}

			ToPlayer.Z = 150.f;
		}

		bool bResult = MoveToPointWithSpeed(ToPlayer, Speed);
		if (!bResult)
		{
			bReachedDest = true;
			ToPlayer = FVector::ZeroVector;
			MoveStatus = EBossMovementStatus::BMS_Max;
			bPastPlayer = false;
		}
		return bResult;
	}

	if (FVector::Dist2D(GetActorLocation(), Player->GetActorLocation()) < 800.f)
	{
		bPastPlayer = true;
		return true;
	}

	FAIMoveRequest AIMoveReq(Player);
	AIController->MoveTo(AIMoveReq);

	return true;
}

