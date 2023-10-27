// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "Potion.h"
#include "PoisonPotion.h"
#include "MOBA_CHARACTER.generated.h"

UCLASS()
class MYPROJECT_API AMOBA_CHARACTER : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMOBA_CHARACTER();

protected:
	float sprintCooldown = 0.f;
	float sprintDuration = 0.f;
	bool sprinting = false;
	bool sprintReady = true;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere);
	TSubclassOf<APotion> potionClass;

	UPROPERTY(EditAnywhere);
	TSubclassOf<APoisonPotion> poisonPotionClass;

	// Called every frame
	void Tick(float DeltaTime) override;

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	//Auto Attack
	void Potion(const FInputActionValue& Value, bool healing);

	// Sprint
	void Sprint(const FInputActionValue& value);




};
