// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "PlayerCharacterState.generated.h"

/**
 * 
 */
class UAbilitySystemComponent;
class UAttributeSet;
UCLASS()
class UE5_ARPG_PROJECT_API APlayerCharacterState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerCharacterState();
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	UAttributeSet* GetAttributeSet() const { return AttributeSet; }

protected:
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
};