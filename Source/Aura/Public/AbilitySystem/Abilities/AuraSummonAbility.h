// Copyright Iron Goblin Corp. 2023

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraSummonAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraSummonAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "Aura|Summoning")
	TArray<FVector> GetSpawnLocations();

	UFUNCTION(BlueprintPure, Category = "Aura|Summoning")
	TSubclassOf<APawn> GetRandomMinionClass();

	UPROPERTY(EditDefaultsOnly, Category = "Aura|Summoning")
	int32 NumMinions = 5;

	UPROPERTY(EditDefaultsOnly, Category = "Aura|Summoning")
	TArray<TSubclassOf<APawn>> MinionClasses;

	UPROPERTY(EditDefaultsOnly, Category = "Aura|Summoning")
	float MinSpawnDistance = 50.f;

	UPROPERTY(EditDefaultsOnly, Category = "Aura|Summoning")
	float MaxSpawnDistance = 250.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Aura|Summoning")
	float SpawnSpread = 90.f;

	

};
