// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/BaseWidgetController.h"
#include "OverlayWidgetController.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLifeChangedSignature, float, NewLife);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaximumLifeChangedSignature, float, NewMaximumLife);


class APlayerAttributeSet;
/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class UE5_ARPG_PROJECT_API UOverlayWidgetController : public UBaseWidgetController
{
	GENERATED_BODY()

public:
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnLifeChangedSignature OnLifeChanged;

	UPROPERTY(BlueprintAssignable, Category="GAS|Attributes")
	FOnMaximumLifeChangedSignature OnMaximumLifeChanged;

protected:
	void LifeChanged(const FOnAttributeChangeData& Data) const;
	void MaximumLifeChanged(const FOnAttributeChangeData& Data) const;
	
};
