// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "GameFramework/Character.h"
#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "PlayerAttributeSet.generated.h"


//accessors macro
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

// Struct to retrieve all the different Data for use in PostGameplayEffectExecute
USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}
	UPROPERTY()
	FGameplayEffectContextHandle  EffectContextHandle;

	//  -- SOURCE --
	UPROPERTY()
	UAbilitySystemComponent* SourceAbilitySystemComponent = nullptr;
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;
	UPROPERTY()
	AController* SourceController = nullptr;
	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	// -- TARGET --
	UPROPERTY()
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;
	UPROPERTY()
	AController* TargetController = nullptr;
	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
};

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

	//clamping - only good for clamping
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	// useful for any other logic too
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category="Life")
	FGameplayAttributeData Life;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Life);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaximumLife, Category="Life")
	FGameplayAttributeData MaximumLife;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaximumLife);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category="Mana")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaximumMana, Category="Mana")
	FGameplayAttributeData MaximumMana;
	ATTRIBUTE_ACCESSORS(UPlayerAttributeSet, MaximumMana);
	

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldLife) const;

	UFUNCTION()
	void OnRep_MaximumLife(const FGameplayAttributeData& OldMaximumLife) const;

	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_MaximumMana(const FGameplayAttributeData& OldMaximumMana) const;

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	
	
};
