// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyTower.h"
#include "Tank.h"
#include "ScreenText_Widget.h"
//#include "HeathWidget.h"


#include "BB_GameMode.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API ABB_GameMode : public AGameModeBase
{
	GENERATED_BODY()
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;





public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UScreenText_Widget>ScreenText_WidgetClass;

	UScreenText_Widget* ScreenText_Widget_widget;







		ATank* Tank;
	int32 TowerCount;

	void ActorDied(AActor* DeadActor);

	UPROPERTY(EditAnywhere)
	float GameOverDelay = 3.0f;

	UPROPERTY(EditAnywhere)
	int32 CountDownDelay = 4;
	int32 CountdownSeconds;

	FTimerHandle CountDownTimerHandle;

	void OnCountDownTimerTimeOut();

	void OnGameOverTimerTimeout();
	bool IsGameOver = false;
	bool IsVictory = false;

	/*UPROPERTY(EditAnywhere)
	TSubclassOf<UHeathWidget>HeathWidget;

	UPROPERTY(VisibleAnywhere)
	UHeathWidget* HeathW;*/

	
};
