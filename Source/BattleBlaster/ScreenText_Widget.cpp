// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenText_Widget.h"

void UScreenText_Widget::SetMessageText(FString Message)
{
	FText MessageText = FText::FromString(Message);
	GetReadyTEXT->SetText(MessageText);



}
