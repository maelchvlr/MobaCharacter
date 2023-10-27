// Fill out your copyright notice in the Description page of Project Settings.


#include "MOBA_CHARACTER.h"
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("sprint ready"));
	}

	if (sprintDuration > 0)
	{
		sprintDuration -= DeltaTime;
	}
	else if (sprintDuration < 0 && sprinting)
	{
		sprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = 600.0f;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("sprint off"));
	}

	if (healCooldown > 0)
	{
		healCooldown -= DeltaTime;
	}
	else if (healCooldown < 0 && !healThrowable)
	{
		healThrowable = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("heal ready"));

	}

	if (poisonCooldown > 0)
	{
		poisonCooldown -= DeltaTime;
	}
	else if (poisonCooldown < 0 && !poisonThrowable)
	{
		poisonThrowable = true;
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("poison ready"));

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

void AMOBA_CHARACTER::Potion(const FInputActionValue& Value, bool healing)
{
	APlayerCameraManager* playerCamera = GetWorld()->GetFirstPlayerController() ? GetWorld()->GetFirstPlayerController()->PlayerCameraManager : nullptr;
	

	FVector viewDirection = playerCamera->GetActorForwardVector();
	float distanceInFront = 50.0f;

	FVector Location = GetActorLocation() + (viewDirection * distanceInFront);
	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;

	float forwardImpulseIntensity = 500.0f;
	float upwardImpulseIntensity = 500.0f;
	FVector totalImpulse = (viewDirection * forwardImpulseIntensity) + (FVector::UpVector * upwardImpulseIntensity);

	if (healing)
	{
		if (healThrowable)
		{
			healThrowable = false;
			healCooldown = 1.5f;
			APotion* spawnedPotion = GetWorld()->SpawnActor<APotion>(potionClass, Location, Rotation, SpawnInfo);
			if (spawnedPotion && spawnedPotion->getMesh())
			{
				spawnedPotion->getMesh()->AddImpulse(totalImpulse, NAME_None, true);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("heal on cooldown"));
		}
	}
	else
	{
		if (poisonThrowable)
		{
			poisonThrowable = false;
			poisonCooldown = 5.f;
			APoisonPotion* spawnedPotion = GetWorld()->SpawnActor<APoisonPotion>(poisonPotionClass, Location, Rotation, SpawnInfo);
			if (spawnedPotion && spawnedPotion->getMesh())
			{
				spawnedPotion->getMesh()->AddImpulse(totalImpulse, NAME_None, true);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("poison on cooldown"));
		}
	}
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
