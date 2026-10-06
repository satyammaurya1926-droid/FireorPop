// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{

	SpringArmcomp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmcomp->SetupAttachment(CapsuleComp);

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SpringArmcomp);










}




void ATank::BeginPlay()
{
	Super::BeginPlay();

	// This class control the pawn in game.Controller
	PlayerController = Cast<APlayerController>(Controller);
	if (PlayerController)
	{




		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		{


			if (UEnhancedInputLocalPlayerSubsystem*
				Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer))
			{


				Subsystem->AddMappingContext(DefaultMappingContext, 0);

			}



		}









	}


	SetPlayerEnabled(false);












}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



	
	if (PlayerController)
	{

		FHitResult HitResult;
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

		RotateTurret(HitResult.ImpactPoint);



		//DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.0f, 12, FColor::Black);	












	}

	












}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);




	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>
		(PlayerInputComponent))

	{

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATank::MoveInput);

		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATank::TurnInput);

		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ATank::Fire);


	}













}

void ATank::MoveInput(const FInputActionValue& Value)
{

	float InputValue = Value.Get<float>();




	//UE_LOG(LogTemp, Display, TEXT("Input Value %f"), InputValue);

	FVector DeltaLocation = FVector(0.0f, 0.0f, 0.0f);
	DeltaLocation.X = Speed * InputValue * UGameplayStatics::GetWorldDeltaSeconds(GetWorld());
	AddActorLocalOffset(DeltaLocation, true);






}

void ATank::TurnInput(const FInputActionValue& Value)
{

	float TurnInput = Value.Get<float>();
	FRotator DeltaRotation = FRotator(0.0f, 0.0f, 0.0f);
	DeltaRotation.Yaw = TurnRate * TurnInput * GetWorld()->GetDeltaSeconds();
	AddActorLocalRotation(DeltaRotation, true);








}

void ATank::HandleDestruction()
{
	Super::HandleDestruction();

	//UE_LOG(LogTemp, Display, TEXT("Tank Destroyed"));

	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);
	SetPlayerEnabled(false);
	
	
	
	IsAlive = false;








}

void ATank::SetPlayerEnabled(bool Enabled)
{

	if (PlayerController)
	{

		








		if (Enabled)
		{

			EnableInput(PlayerController);	
			PlayerController->bShowMouseCursor = true;

		}
		else
		{

			DisableInput(PlayerController);	
			PlayerController->bShowMouseCursor = false;



		}











	}








}

/*void ATank::UpdateHeathWidget()
{

	ATank* playercontroller = Cast<ATank>(GetController());
	if (playercontroller)
	{

		
		float NewPercent = Health / MaxHealth;


		playercontroller->HeathWidget->SetHealthBarPercent(NewPercent);



	}





}*/


