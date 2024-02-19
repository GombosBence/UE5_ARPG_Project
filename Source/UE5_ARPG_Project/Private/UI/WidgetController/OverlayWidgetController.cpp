// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/WidgetController/OverlayWidgetController.h"
#include "Abilitysystem/PlayerAttributeSet.h"

class UPlayerAttributeSet;

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UPlayerAttributeSet* PlayerAttributeSet = CastChecked<UPlayerAttributeSet>(AttributeSet);
	OnLifeChanged.Broadcast(PlayerAttributeSet->GetLife());
	OnMaximumLifeChanged.Broadcast(PlayerAttributeSet->GetMaximumLife());
	OnManaChanged.Broadcast(PlayerAttributeSet->GetMana());
	OnMaximumManaChanged.Broadcast(PlayerAttributeSet->GetMaximumMana());
	
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UPlayerAttributeSet* PlayerAttributeSet = CastChecked<UPlayerAttributeSet>(AttributeSet);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetLifeAttribute())
		.AddUObject(this, &UOverlayWidgetController::LifeChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetMaximumLifeAttribute())
		.AddUObject(this, &UOverlayWidgetController::MaximumLifeChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetManaAttribute())
		.AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(PlayerAttributeSet->GetMaximumManaAttribute())
		.AddUObject(this, &UOverlayWidgetController::MaximumManaChanged);
}

void UOverlayWidgetController::LifeChanged(const FOnAttributeChangeData& Data) const
{
	
	OnLifeChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaximumLifeChanged(const FOnAttributeChangeData& Data) const
{
	OnMaximumLifeChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaximumManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaximumManaChanged.Broadcast(Data.NewValue);
}
