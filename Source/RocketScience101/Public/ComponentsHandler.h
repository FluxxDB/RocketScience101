// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/DataTable.h"
#include "Containers/Array.h"
#include "Math/UnrealMathUtility.h"

#include "ComponentsHandler.generated.h"

USTRUCT(BlueprintType)
struct FRocketComponent : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString ComponentType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		int32 Potential;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		AActor* Actor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		double SpawnRate;
};

UCLASS()
class ROCKETSCIENCE101_API AComponentsHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AComponentsHandler();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Rocket Component System")
	void SpawnRandomComponent();

	UPROPERTY(EditAnywhere);
	class UDataTable* RocketComponentsDataTable;

private:
	double totalWeight;
	TMap<double, FRocketComponent> componentWeightBounds;
};
