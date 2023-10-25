// Fill out your copyright notice in the Description page of Project Settings.


#include "PC_MOBA.h"
#include "MOBA_CHARACTER.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void APC_MOBA::BeginPlay()
{
    Super::BeginPlay();

    character = CastChecked<AMOBA_CHARACTER>(GetPawn());

    if (UEnhancedInputLocalPlayerSubsystem* input_subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        input_subsystem->AddMappingContext(DefaultMappingContext, 0);
    }

    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(character->InputComponent))
    {
        // Jumping
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, character, &ACharacter::Jump);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, character, &ACharacter::StopJumping);

        // Moving
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, character, &AMOBA_CHARACTER::Move);

        // Looking
        EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, character, &AMOBA_CHARACTER::Look);

        // Attack
        EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, character, &AMOBA_CHARACTER::Attack);

        // Sprint
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Triggered, character, &AMOBA_CHARACTER::Sprint);
    }
}
