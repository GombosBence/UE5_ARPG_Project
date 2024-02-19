// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "Abilitysystem/PlayerAttributeSet.h"

class UPlayerAttributeSet;

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UPlayerAttributeSet* PlayerAttributeSet = CastChecked<UPlayerAttributeSet>(AttributeSet);
	OnLifeChanged.Broadcast(PlayerAttributeSet->GetLife());
	OnMaximumLifeChanged.Broadcast(PlayerAttributeSet->GetMaximumLife());
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UPlayerAttributeSet* PlayerAttributeSet = CastChecked<UPlayerAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetLifeAttribute())
		.AddUObject(this, &UOverlayWidgetController::LifeChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetMaximumLifeAttribute())
		.AddUObject(this, &UOverlayWidgetController::MaximumLifeChanged);
}

void UOverlayWidgetController::LifeChanged(const FOnAttributeChangeData& Data) const
{
	
	OnLifeChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaximumLifeChanged(const FOnAttributeChangeData& Data) const
{
	OnMaximumLifeChanged.Broadcast(Data.NewValue);
}
