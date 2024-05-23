// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EffectActor.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

// Sets default values
AEffectActor::AEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	//Any type of mesh can be added to the root component
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}




void AEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

//On overlap this will be called on blueprint side
void AEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass, EEffectRemovalPolicy RemovalPolicy)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if(TargetAbilitySystemComponent == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle GameplayEffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();
	//Adds what caused the effect to the context
	GameplayEffectContextHandle.AddSourceObject(this);
	//Allows blueprints to generate a GameplayEffectSpec once and then reference it by handle, to apply it multiple times/multiple targets. 
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, GameplayEffectContextHandle);
	const FActiveGameplayEffectHandle ActiveGameplayEffectHandle = TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	//Get the gameplay effect from the SpecHandle
	if (EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite
		&& RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		//The handle stores the ActiveGameplayEffect, the TargetAbilitySystem component is what the first line gets from the specific Actor
		ActiveEffectHandles.Add(ActiveGameplayEffectHandle, TargetAbilitySystemComponent);
	}
}

void AEffectActor::OnOverlap(AActor* TargetActor)
{
	for (const TTuple<TSubclassOf<UGameplayEffect>, FEffectPolicies> EffectArray : GameplayEffectArray)
	{
		if(EffectArray.Value.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetActor, EffectArray.Key, EffectArray.Value.RemovalPolicy);
		}
	}
	
	/*
	if(InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}
	if(DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}
	if(InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
	*/
}

void AEffectActor::OnEndOverlap(AActor* TargetActor)
{
	for (const TTuple<TSubclassOf<UGameplayEffect>, FEffectPolicies> EffectArray : GameplayEffectArray)
	{
		if(EffectArray.Value.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetActor, EffectArray.Key, EffectArray.Value.RemovalPolicy);
		}
		if(EffectArray.Value.RemovalPolicy ==  EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
			TArray<FActiveGameplayEffectHandle> RemovableHandles;
			for (const TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandle : ActiveEffectHandles)
			{
				if(ActiveEffectHandle.Value == TargetAbilitySystemComponent)
				{
					TargetAbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffectHandle.Key, 1);
					RemovableHandles.Add(ActiveEffectHandle.Key);
				}
			}
			for (auto& RemovableHandle : RemovableHandles)
			{
				ActiveEffectHandles.FindAndRemoveChecked(RemovableHandle);
			}
		}
	}
	/*
	if(InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		TArray<FActiveGameplayEffectHandle> RemovableHandles;
		for (const TTuple<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandle : ActiveEffectHandles)
		{
			if(ActiveEffectHandle.Value == TargetAbilitySystemComponent)
			{
				TargetAbilitySystemComponent->RemoveActiveGameplayEffect(ActiveEffectHandle.Key, 1);
				RemovableHandles.Add(ActiveEffectHandle.Key);
			}
		}
		for (auto& RemovableHandle : RemovableHandles)
		{
			ActiveEffectHandles.FindAndRemoveChecked(RemovableHandle);
		}
	}
	*/
}



