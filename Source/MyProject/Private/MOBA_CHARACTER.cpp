// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBA_CHARACTER.h"
#include "Potion.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AMOBA_CHARACTER::AMOBA_CHARACTER() 
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	GetCharacterMovement()->MaxWalkSpeed = 600.0f;
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AMOBA_CHARACTER::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMOBA_CHARACTER::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (sprintCooldown > 0)
	{
		sprintCooldown -= DeltaTime;
	}
	else if (sprintCooldown < 0 && !sprintReady)
	{
		sprintReady = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("sirpnt ready"));
	}

	if (sprintDuration > 0)
	{
		sprintDuration -= DeltaTime;
	}
	else if (sprintDuration < 0 && sprinting)
	{
		sprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("sirpnt off"));
	}

}


void AMOBA_CHARACTER::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AMOBA_CHARACTER::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AMOBA_CHARACTER::Attack(const FInputActionValue& Value)
{
	// Get the player's forward direction
	APlayerCameraManager* playerCamera = GetWorld()->GetFirstPlayerController()->PlayerCameraManager;
	FVector viewDirection = playerCamera->GetActorForwardVector();



	// Set the distance you want the sphere to spawn in front of the player
	float distanceInFront = 50.0f;

	// Calculate the new spawn location
	FVector Location = GetActorLocation() + (viewDirection * distanceInFront);

	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;

	APotion* spawnedPotion = GetWorld()->SpawnActor<APotion>(potionClass, Location, Rotation, SpawnInfo);

	float forwardImpulseIntensity = 500.0f; 
	float upwardImpulseIntensity = 500.0f;   

	FVector totalImpulse = (viewDirection * forwardImpulseIntensity) + (FVector::UpVector * upwardImpulseIntensity);
	spawnedPotion->getMesh()->AddImpulse(totalImpulse, NAME_None, true);


}

void AMOBA_CHARACTER::Sprint(const FInputActionValue& value)
{
	if (sprintReady)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("sirpnt"));
		sprintDuration = 5.f;
		sprintCooldown = 15.f;
		GetCharacterMovement()->MaxWalkSpeed = 1200.0f;
		sprinting = true;
		sprintReady = false;
	}
}
