// Copyright Iron Goblin Corp. 2023

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();

	//~ AActor Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ end AActor Interface.

	virtual void OnRep_PlayerState() override;

protected:
	void InitAbilityActorInfo() override;
};
