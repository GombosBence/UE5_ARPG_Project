// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameFramework/Actor.h"
#include "EffectActor.generated.h"

class UAbilitySystemComponent;
class UGameplayEffect;


UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};
UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnEndOverlap,
	DoNotRemove
};
USTRUCT(BlueprintType)
struct FEffectPolicies
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects")
	EEffectApplicationPolicy ApplicationPolicy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Effects")
	EEffectRemovalPolicy RemovalPolicy;
};
UCLASS()
class UE5_ARPG_PROJECT_API AEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEffectActor();


protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bDestroyOnEffectRemoval = false;

	
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass, EEffectRemovalPolicy RemovalPolicy);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);
	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	TMap<TSubclassOf<UGameplayEffect>, FEffectPolicies> GameplayEffectArray;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	//Policy on how the different effects are applied and removed

	/*
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Effects")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;
	*/
	//Map to store infinite effects so they can be removed manually
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;
	
};
