// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class UE5_ARPG_PROJECT_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEffectActor();


protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, Category="Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	
};
