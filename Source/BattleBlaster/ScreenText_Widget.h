// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"



#include "ScreenText_Widget.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEBLASTER_API UScreenText_Widget : public UUserWidget
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnyWhere, meta = (BindWidget))
	UTextBlock* GetReadyTEXT;

	void SetMessageText(FString Message);























};
