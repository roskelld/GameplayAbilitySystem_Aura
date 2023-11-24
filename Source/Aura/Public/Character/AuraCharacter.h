// Copyright Iron Goblin Corp. 2023

#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "Interaction/PlayerInterface.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase, public IPlayerInterface
{
	GENERATED_BODY()
	
public:
	AAuraCharacter();

	//~ AActor Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ end AActor Interface.

	virtual void OnRep_PlayerState() override;

	//~ Player Interface
	virtual void AddToXP_Implementation(int32 InXP) override;
	//~ end Player Interface

	//~ Combat Interface
	virtual int32 GetPlayerLevel() override;
	//~ end Combat Interface.

protected:
	void InitAbilityActorInfo() override;
};
