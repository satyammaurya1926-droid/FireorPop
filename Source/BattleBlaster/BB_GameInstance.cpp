// Fill out your copyright notice in the Description page of Project Settings.


#include "BB_GameInstance.h"
#include "Kismet/GameplayStatics.h"



void UBB_GameInstance::ChangeLevel(int32 Index)
{

	if (Index > 0 && Index <= LastLevelIndex)
	{
		CurrentLevelIndex = Index;

		FString LevelNameString = FString::Printf(TEXT("Level%d"), CurrentLevelIndex);

		UGameplayStatics::OpenLevel(GetWorld(), *LevelNameString);

	}








}
void UBB_GameInstance::LoadNextLevel()
{
	if (CurrentLevelIndex < LastLevelIndex)
	{


		ChangeLevel(CurrentLevelIndex + 1);

	}
	else
	{

		RestartGame();


	}


}

void UBB_GameInstance::RestartCurrentLevel()
{

	ChangeLevel(CurrentLevelIndex);

}

void UBB_GameInstance::RestartGame()
{

	ChangeLevel(1);


}