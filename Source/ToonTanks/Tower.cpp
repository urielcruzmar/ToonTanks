// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	// Check if in range
	if (InFireRange())
	{
		// Rotate turret to Tank
		RotateTurret(Tank->GetActorLocation());
	}
}

void ATower::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));

	GetWorldTimerManager().SetTimer(
		FireRateTimerHandle,
		this,
		&ATower::CheckFireCondition,
		FireRate,
		true);
}

void ATower::CheckFireCondition()
{
		if (InFireRange())
		{
			Fire();
		}
}

bool ATower::InFireRange() const
{
	if (Tank)
	{
		return FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) < FireRange;
	}
	return false;
}
