// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/PlayerAttributeSet.h"
#include "abilitysystemcomponent.h"
#include "Net/UnrealNetwork.h"

UPlayerAttributeSet::UPlayerAttributeSet()
{
	InitLife(75.f);
	InitMaximumLife(100.f);
	InitMana(25.f);
	InitMaximumMana(50.f);
}

void UPlayerAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//register variables for replication
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Life, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MaximumLife, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UPlayerAttributeSet, MaximumMana, COND_None, REPNOTIFY_Always);
}

void UPlayerAttributeSet::OnRep_Health(const FGameplayAttributeData& OldLife) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Life, OldLife);
}

void UPlayerAttributeSet::OnRep_MaximumLife(const FGameplayAttributeData& OldMaximumLife) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MaximumLife, OldMaximumLife);
}

void UPlayerAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, Mana, OldMana);
}

void UPlayerAttributeSet::OnRep_MaximumMana(const FGameplayAttributeData& OldMaximumMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UPlayerAttributeSet, MaximumMana, OldMaximumMana);
}
