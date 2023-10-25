// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PotionPuddle.generated.h"

UCLASS()
class MYPROJECT_API APotionPuddle : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* puddleMesh;

	// Sets default values for this actor's properties
	APotionPuddle();

	UStaticMeshComponent* getMesh() { return puddleMesh; }

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


protected:
	float puddleTimer;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	void Tick(float DeltaTime) override;

};
