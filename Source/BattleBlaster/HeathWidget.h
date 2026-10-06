// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"

#include "HeathWidget.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API UHeathWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnyWhere, meta = (BindWidget))
	UProgressBar* HealthBar;

	void SetHealthBarPercent(float NewPercent);
};
