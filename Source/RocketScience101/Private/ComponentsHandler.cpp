// Fill out your copyright notice in the Description page of Project Settings.

#include "ComponentsHandler.h"

// Sets default values
AComponentsHandler::AComponentsHandler()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Loads component data table (Doesn't work?)

	/*static ConstructorHelpers::FObjectFinder<UDataTable> ComponentsDataTableObject(TEXT("DataTable'/Game/Components/DT_Components.DT_Components'"));
	if (ComponentsDataTableObject.Succeeded())
	{
		RocketComponentsDataTable = ComponentsDataTableObject.Object;
	}*/
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
		totalWeight += component->SpawnRate;
		componentWeightBounds.Add(totalWeight, *component);
	}
}

// Called every frame
void AComponentsHandler::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Spawns a random component at a random position
void AComponentsHandler::SpawnRandomComponent()
{
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Magenta, TEXT("aaaaaa"));
	if (!GEngine) return;

	if (!RocketComponentsDataTable) return;

	const TArray<FName> RocketComponents = RocketComponentsDataTable->GetRowNames();
	const int RocketComponentsSize = RocketComponents.Num();

	const FString& ContextString(TEXT("Rocket Component Context"));
	const FName componentIndex = *(componentWeightBounds.Find(FMath::FRandRange(0, totalWeight)))->Name;
	const FRocketComponent* RocketComponent = RocketComponentsDataTable->FindRow<FRocketComponent>(componentIndex, ContextString, true);

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Magenta, componentIndex.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Magenta, RocketComponent->Name);
}

