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

void AEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);
	if(TargetAbilitySystemComponent == nullptr) return;

	check(GameplayEffectClass);
	FGameplayEffectContextHandle GameplayEffectContextHandle = TargetAbilitySystemComponent->MakeEffectContext();
	//Adds what caused the effect to the context
	GameplayEffectContextHandle.AddSourceObject(this);
	//Allows blueprints to generate a GameplayEffectSpec once and then reference it by handle, to apply it multiple times/multiple targets. 
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetAbilitySystemComponent->MakeOutgoingSpec(GameplayEffectClass, 1.f, GameplayEffectContextHandle);
	TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
	
}


