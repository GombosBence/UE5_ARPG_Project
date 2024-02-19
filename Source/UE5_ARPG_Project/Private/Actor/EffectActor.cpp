// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/EffectActor.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystem/PlayerAttributeSet.h"
#include "Components/SphereComponent.h"

// Sets default values
AEffectActor::AEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Mesh);
	Sphere->SetupAttachment(GetRootComponent());
	
}

void AEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//TODO: Change this to apply a GameplayEffect. This is a hack.
	if(IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UPlayerAttributeSet* PlayerAttributeSet = Cast<UPlayerAttributeSet>
		(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UPlayerAttributeSet::StaticClass()));

		UPlayerAttributeSet* MutablePlayerAttributeSet = const_cast<UPlayerAttributeSet*>(PlayerAttributeSet);
		MutablePlayerAttributeSet->SetLife(MutablePlayerAttributeSet->GetLife() + 25.f);
		MutablePlayerAttributeSet->SetMana(MutablePlayerAttributeSet->GetMana() - 25.f);
		Destroy();
	}
}

void AEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}


void AEffectActor::BeginPlay()
{
	Super::BeginPlay();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AEffectActor::OnOverlap);
	Sphere->OnComponentEndOverlap.AddDynamic(this, &AEffectActor::EndOverlap);
	
}


