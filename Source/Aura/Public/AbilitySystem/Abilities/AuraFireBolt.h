// Copyright Iron Goblin Corp. 2023

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "AuraFireBolt.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraFireBolt : public UAuraProjectileSpell
{
	GENERATED_BODY()
public:

	virtual FString GetDescription(int32 Level) override;
	virtual FString GetNextLevelDescription(int32 NextLevel) override;
};
