// Fill out your copyright notice in the Description page of Project Settings.


#include "BB_GameMode.h"
#include "BB_GameInstance.h"
#include "EnemyTower.h"

void ABB_GameMode::BeginPlay()
{
	Super::BeginPlay();


	TArray<AActor*>EnemyTower;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemyTower::StaticClass(), EnemyTower);
	TowerCount = EnemyTower.Num();

	UE_LOG(LogTemp, Display, TEXT("Tower Count %d"), TowerCount);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (PlayerPawn)
	{

		Tank = Cast<ATank>(PlayerPawn);
		if (!Tank)
		{

			UE_LOG(LogTemp, Display, TEXT("Tank Not  Found"));



		}





	}
	UE_LOG(LogTemp, Display, TEXT("loop start"));
	int32 loopindex = 0;
	while (loopindex < TowerCount)
	{


		//UE_LOG(LogTemp, Display, TEXT("loop index: %d"),loopindex);
		AActor* TowerActor = EnemyTower[loopindex];
		if (TowerActor)
		{
			AEnemyTower* Tower = Cast<AEnemyTower>(TowerActor);
			if (Tower && Tank)
			{

				Tower->Tank = Tank;
				//UE_LOG(LogTemp, Display, TEXT("%s"), *Tower->GetActorNameOrLabel());

			}


		}
		
		loopindex++;


	}
	//UE_LOG(LogTemp, Display, TEXT("loop end"));

	APlayerController* PlayerContoller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerContoller)
	{

		ScreenText_Widget_widget = CreateWidget<UScreenText_Widget>(PlayerContoller, ScreenText_WidgetClass);
		if (ScreenText_Widget_widget)
		{

			ScreenText_Widget_widget->AddToPlayerScreen();
			ScreenText_Widget_widget->SetMessageText("Get Ready!");



		}



	}

	/*HeathW = CreateWidget<UHeathWidget>(PlayerContoller, HeathWidget);
	if (HeathW)
	{

		HeathW->AddToPlayerScreen();
		



	}*/
	





	CountdownSeconds = CountDownDelay;

	GetWorldTimerManager().SetTimer(CountDownTimerHandle, this, &ABB_GameMode::OnCountDownTimerTimeOut, 1.0f, true);



	//countdown system that attacted to void ABB_GameMode::OnCountDownTimerTimeOut()






}

void ABB_GameMode::OnCountDownTimerTimeOut()
{


	CountdownSeconds -= 1;

	if (CountdownSeconds > 0)
	{
		//UE_LOG(LogTemp, Display, TEXT("countdown: %d"), CountdownSeconds);
		
		ScreenText_Widget_widget->SetMessageText(FString::FromInt(CountdownSeconds));



	}
	else if(CountdownSeconds==0 )
	{
		//UE_LOG(LogTemp, Display, TEXT("Go!"));
		ScreenText_Widget_widget->SetMessageText("Go!");
		Tank->SetPlayerEnabled(true);




	}
	else
	{
		//CoundownSecond is less then 0

		GetWorldTimerManager().ClearTimer(CountDownTimerHandle);

		//UE_LOG(LogTemp, Display, TEXT("ClearTimer"));
		ScreenText_Widget_widget->SetVisibility(ESlateVisibility::Hidden);

	}







}





void ABB_GameMode::ActorDied(AActor* DeadActor)
{

	




	if (DeadActor == Tank)
	{


		Tank->HandleDestruction();
		IsGameOver = true;


	}
	else
	{
	
		AEnemyTower* DeadTower = Cast<AEnemyTower>(DeadActor);
		if (DeadTower)
		{


			DeadTower->HandleDestruction();

			

			TowerCount--;
			if (TowerCount == 0)
			{
				IsGameOver = true;
				IsVictory = true;


			}

		}
	
		
	
	
	}
	if (IsGameOver)
	{
		FString GameOverString = IsVictory ? "Victory!" : "Defeat";


		//UE_LOG(LogTemp, Display, TEXT("Game Over: %s"), *GameOverString);

		ScreenText_Widget_widget->SetMessageText(GameOverString);
		ScreenText_Widget_widget->SetVisibility(ESlateVisibility::Visible);





		/*if (IsVictory)
		{
			GameOverString = TEXT("Victory");


		}
		else
		{
			GameOverString = TEXT("Defeat");



		}*/

		//IsVictory ? "victory" : "defeat"; -> Ternary operator
		//Statement ? True : False;
		//__________________________________________________________

		FTimerHandle GameOverTimerHandle;

		GetWorldTimerManager().SetTimer(GameOverTimerHandle, this, &ABB_GameMode::OnGameOverTimerTimeout, GameOverDelay, false);

	}

	


}



void ABB_GameMode::OnGameOverTimerTimeout()
{

	//UE_LOG(LogTemp, Display, TEXT("Game Over Timer Timeout"));

	//FString CurrentLevel = UGameplayStatics::GetCurrentLevelName(GetWorld());
	//GetGameInstance();  // To load Levels
	 

	UGameInstance* GameInstance =  GetGameInstance();
	if (GameInstance)
	{



		UBB_GameInstance* BB_GameInstance = Cast<UBB_GameInstance>(GameInstance);
		if (BB_GameInstance)
		{
			if (IsVictory)
			{ // load Next level
				BB_GameInstance->LoadNextLevel();

			}
			else
			{ // load current level 

				BB_GameInstance->RestartCurrentLevel();


			}



		}



	}


	


}
