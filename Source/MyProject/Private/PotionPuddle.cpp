// Fill out your copyright notice in the Description page of Project Settings.


#include "PotionPuddle.h"
#include "MOBA_CHARACTER.h"

// Sets default values
APotionPuddle::APotionPuddle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	puddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PuddleMesh"));
    puddleTimer = 0.5f;

}

void APotionPuddle::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor->IsA(AMOBA_CHARACTER::StaticClass()))
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Player stepped in the puddle!"));
        // Handle what you want to happen when the player steps in the puddle here.
    }
}

// Called when the game starts or when spawned
void APotionPuddle::BeginPlay()
{
	Super::BeginPlay();
	puddleMesh->OnComponentBeginOverlap.AddDynamic(this, &APotionPuddle::OnOverlap);

}

// Called every frame
void APotionPuddle::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    puddleTimer -= DeltaTime;
    if (puddleTimer < 0.f)
    {
        Destroy();
    }

}

