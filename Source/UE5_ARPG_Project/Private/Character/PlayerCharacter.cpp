// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/MainCharacterController.h"
#include "Player/PlayerCharacterState.h"
#include "UI/HUD/MHUD.h"

APlayerCharacter::APlayerCharacter()
{
	//make character orient towards movement
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	//Character should not use controller's rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;

	//ZOOM
	// Create CameraBoom (spring arm component)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1200.0f;
	CameraBoom->bUsePawnControlRotation = false;
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;

	// Create CameraComponent
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(CameraBoom);
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	//Init ability actor info for the server
	InitAbilityActorInfo();
	
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init ability actor info for the client
	InitAbilityActorInfo();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	if(APlayerCharacterState* PlayerCharacterState = GetPlayerState<APlayerCharacterState>())
	{
		PlayerCharacterState->GetAbilitySystemComponent()->InitAbilityActorInfo(PlayerCharacterState, this);

		//Init components
		AbilitySystemComponent = PlayerCharacterState->GetAbilitySystemComponent();
		AttributeSet = PlayerCharacterState->GetAttributeSet();

		if(AMainCharacterController* MainCharacterController = Cast<AMainCharacterController>(GetController()))
		{
			if(AMHUD* Amhud = Cast<AMHUD>(MainCharacterController->GetHUD()))
			{
				Amhud->InitOverlay(MainCharacterController, PlayerCharacterState, AbilitySystemComponent, AttributeSet);
			}
		}
	}
	else
	{
		//Nullptr
	}
	
}
