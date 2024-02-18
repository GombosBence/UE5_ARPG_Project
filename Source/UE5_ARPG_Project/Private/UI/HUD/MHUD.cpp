// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUD/MHUD.h"

#include "Blueprint/UserWidget.h"

void AMHUD::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	Widget->AddToViewport();
}
