// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "PlayerAttributeSet.generated.h"

/**
 * 
 */
UCLASS()
class UE5_ARPG_PROJECT_API UPlayerAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UPlayerAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category="Life")
	FGameplayAttributeData Life;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaximumLife, Category="Life")
	FGameplayAttributeData MaximumLife;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category="Mana")
	FGameplayAttributeData Mana;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaximumMana, Category="Mana")
	FGameplayAttributeData MaximumMana;
	

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldLife) const;

	UFUNCTION()
	void OnRep_MaximumLife(const FGameplayAttributeData& OldMaximumLife) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_MaximumMana(const FGameplayAttributeData& OldMaximumMana) const;
	
	
};
