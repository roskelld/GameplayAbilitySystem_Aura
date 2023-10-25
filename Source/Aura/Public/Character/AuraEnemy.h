// Copyright Iron Goblin Corp. 2023

#pragma once

#include "CoreMinimal.h"
#include "Interaction/EnemyInterface.h"
#include "Character/AuraCharacterBase.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
	
public:
	AAuraEnemy();

	//~ Enemy Interface.
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;
	//~ end Enemy Interface.

	//~ Combat Interface.
	virtual int32 GetPlayerLevel() override;
	//~ end Combat Interface.

protected:
	virtual void BeginPlay() override;

	void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character Class Defaults")
	int32 Level = 1;
};
