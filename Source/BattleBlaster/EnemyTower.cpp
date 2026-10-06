// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyTower.h"

void AEnemyTower::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle FireRateTimerHandle;

	GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &AEnemyTower::CheckFireCondition, FireRate, true);




}

void AEnemyTower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	/*if (Tank)
	{
		float DistanceToTank = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());
		if (DistanceToTank <= FireRange)
		{

			

			

		}



	}*/

	if (IsinFireRange())
	{


		RotateTurret(Tank->GetActorLocation());
		




	}
	
	


}

void AEnemyTower::CheckFireCondition()
{

	//UE_LOG(LogTemp, Display, TEXT("CheckFireCondition called"));

	if (Tank && Tank->IsAlive && IsinFireRange())
	{


		Fire();



	}


}

bool AEnemyTower::IsinFireRange()
{
	bool Result = false;

	if (Tank)
	{
		float DistanceToTank = FVector::Dist(Tank->GetActorLocation(), GetActorLocation());
		Result = (DistanceToTank <= FireRange);
	}

	return Result;
}

void AEnemyTower::HandleDestruction()
{
	
	Super::HandleDestruction();

	Destroy();


	//UE_LOG(LogTemp, Display, TEXT(" ENEMY Died"));
	



}	
