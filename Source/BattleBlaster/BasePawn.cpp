// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"


// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComp"));
	SetRootComponent(CapsuleComp);

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);

	ProjectileSpawnPoint2 = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint2"));
	ProjectileSpawnPoint2->SetupAttachment(TurretMesh);







}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{

	FVector VectortoTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.0f, VectortoTarget.Rotation().Yaw, 0.0f);

	FRotator InterpolatedRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 10.0f);




	TurretMesh->SetWorldRotation(InterpolatedRotation);








}

void ABasePawn::Fire()
{

	FVector SpawnLocation1 = ProjectileSpawnPoint->GetComponentLocation();
	FRotator SpawnRotation1 = ProjectileSpawnPoint->GetComponentRotation();	


	FVector SpawnLocation2 = ProjectileSpawnPoint2->GetComponentLocation();
	FRotator SpawnRotation2 = ProjectileSpawnPoint2->GetComponentRotation();
	//DrawDebugSphere(GetWorld(), SpawnLocation, 25.0f, 12, FColor::Red, false, 2.0f);

	AProjectile* Projectile1 = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation1, SpawnRotation1);
	AProjectile* Projectile2 = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation2, SpawnRotation2);	

	if (Projectile1)
	{
		Projectile1->SetOwner(this);
		
		


	}



	if (Projectile2)
	{
		Projectile2->SetOwner(this);
		
		
	}	

}

void ABasePawn::HandleDestruction()
{

	//UE_LOG(LogTemp, Display, TEXT("BasePawn Destroyed"));
	if (DeathParticles)
	{

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), DeathParticles, GetActorLocation(), GetActorRotation());


	}

	if (DeadSound)
	{



		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeadSound, GetActorLocation());
	}

	if (DeathCameraShakeclass)
	{
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (PlayerController)
		{

			PlayerController->ClientStartCameraShake(DeathCameraShakeclass);

		}

	}


}

