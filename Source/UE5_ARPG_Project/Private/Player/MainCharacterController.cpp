// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/MainCharacterController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "NavigationSystem.h"
#include "Character/PlayerCharacter.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interaction/EnemyInterface.h"

AMainCharacterController::AMainCharacterController()
{
	bReplicates = true;
	
	
}

void AMainCharacterController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
	
}
void AMainCharacterController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	/**
	 *Line trace from cursor. There are several scenarios.
	 * - Last actor is null && thisactor is null
	 *			- Do nothing
	 * - Lastactor is null && this actor is valid
	 *			- Call highlight on this actor
	 * - Lastactor is valid && this actor is null
	 *			- Unhighlight last actor
	 * - Both actors are valid, but Lastactor != Thisactor
	 *			- Unhighlight last actor, and highlight thisactor
	 * - Both actor are valid, and are the same
	 *			- Do nothing
	 */

	if (LastActor == nullptr && ThisActor != nullptr)
	{
		ThisActor->HighlightActor();
	}
	else if (LastActor != nullptr && ThisActor == nullptr)
	{
		LastActor->UnHighlightActor();
	}
	else if (LastActor != nullptr && LastActor != ThisActor)
	{
		LastActor->UnHighlightActor();
		ThisActor->HighlightActor();
	}
}



void AMainCharacterController::BeginPlay()
{
	Super::BeginPlay();
	check(PlayerContext);

	//add input mapping context
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(Subsystem)
	{
		Subsystem->AddMappingContext(PlayerContext, 0);
	}
	//set mouse
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	//able to use input to affect UI elements
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AMainCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	//Cast input component to enhanced input component
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	//Link Move Action with the Move function
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainCharacterController::Move);
	
		
}

void AMainCharacterController::Move(const FInputActionValue& InputActionValue)
{
	/*
	//get X and Y values and Yaw Rotation from InputActionValue
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	//set direction based on Yaw Rotation
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	
	//Add movement input to the controlled pawn
	if(APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
	*/
	
}



