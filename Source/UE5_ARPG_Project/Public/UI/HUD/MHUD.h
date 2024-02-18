// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MHUD.generated.h"

class UBaseUserWidget;
/**
 * 
 */
UCLASS()
class UE5_ARPG_PROJECT_API AMHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY()
	TObjectPtr<UBaseUserWidget> OverlayWidget;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> OverlayWidgetClass;
	
};
