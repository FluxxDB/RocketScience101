// Fill out your copyright notice in the Description page of Project Settings.

#include "ComponentsHandler.h"

// Sets default values
AComponentsHandler::AComponentsHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AComponentsHandler::BeginPlay()
{
	Super::BeginPlay();

	// Assigns components spawn weights (chances)
	if (!RocketComponentsDataTable) return;

	const FString& ContextString(TEXT("Rocket Component Context"));
	const TArray<FName> RocketComponents = RocketComponentsDataTable->GetRowNames();

	for (int i = 0; i < RocketComponents.Num(); i++)
	{
		const FRocketComponent* component = RocketComponentsDataTable->FindRow<FRocketComponent>(RocketComponents[i], ContextString);
		totalWeight += component->SpawnRate * 100;
		componentWeightBounds.Add(component->SpawnRate * 100, *component);
	}
}

// Called every frame
void AComponentsHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Spawns a random component at a random position
FRocketComponent AComponentsHandler::SpawnRandomComponent()
{
	FRocketComponent selectedComponent;

	const TArray<FName> RocketComponents = RocketComponentsDataTable->GetRowNames();
	const int RocketComponentsSize = RocketComponents.Num();

	const FString& ContextString(TEXT("Rocket Component Context"));
	double randomWeight = FMath::FRandRange(0, totalWeight);

	for (auto pair : componentWeightBounds)
	{
		if (randomWeight <= pair.Key)
		{
			selectedComponent = *componentWeightBounds.Find(pair.Key);
			break;
		}
		else
		{
			randomWeight -= pair.Key;
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Magenta, TEXT("Spawn Random Component"));
//	if (selectedComponent != nullptr)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Magenta, selectedComponent->Name);
//	}

	return selectedComponent;
}

