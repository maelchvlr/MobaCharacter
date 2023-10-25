// Fill out your copyright notice in the Description page of Project Settings.


#include "Potion.h"
#include "PotionPuddle.h"

// Sets default values
APotion::APotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	potionMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PotionMesh"));

	


}

void APotion::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	FVector Location = Hit.ImpactPoint + FVector(0, 0, 10);

	FRotator Rotation(0.0f, 0.0f, 0.0f);
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	APotionPuddle* spawnedPotion = GetWorld()->SpawnActor<APotionPuddle>(puddleClass, Location, Rotation, SpawnInfo);

	if (!spawnedPotion)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Failed to spawn puddle!"));
	}

	Destroy();
}

// Called when the game starts or when spawned
void APotion::BeginPlay()
{
	Super::BeginPlay();
	potionMesh->OnComponentHit.AddDynamic(this, &APotion::OnHit);
	
}

// Called every frame
void APotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

