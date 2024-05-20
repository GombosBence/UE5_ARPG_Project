// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacterState.h"

#include "AbilitySystem/BaseAbilitySystemComponent.h"
#include "AbilitySystem/PlayerAttributeSet.h"

APlayerCharacterState::APlayerCharacterState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UBaseAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UPlayerAttributeSet>("AttributeSet");
	
	//How often the server updates clients
	NetUpdateFrequency = 100.f;
}

UAbilitySystemComponent* APlayerCharacterState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
