// Copyright Iron Goblin Corp. 2023

#pragma once

#include "CoreMinimal.h"
#include "Interaction/EnemyInterface.h"
#include "Character/AuraCharacterBase.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/Data/CharacterClassInfo.h"
#include "AuraEnemy.generated.h"

class UWidgetComponent;
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
	virtual void Die() override;
	//~ end Combat Interface.

	/* Using the delegate from OverlayWidgetController to broadcast health changes to UI health bar widget */
	/* This could be derived into its own class and included in both OverlayWidgetController and this also */
	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangedSignature OnMaxHealthChanged;

	void HitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

	UPROPERTY(BlueprintReadonly, Category = "Combat")
	bool bHitReacting = false;

	UPROPERTY(BlueprintReadonly, Category = "Movement")
	float BaseWalkSpeed = 250.f;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Combat")
	float LifeSpan = 5.f;

protected:
	virtual void BeginPlay() override;

	void InitAbilityActorInfo() override;

	virtual void InitializeDefaultAttributes() const override;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character Class Defaults")
	int32 Level = 1;

	UPROPERTY(EditAnywhere, BlueprintReadonly, Category = "Character Class Defaults")
	ECharacterClass CharacterClass = ECharacterClass::Warrior;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	TObjectPtr<UWidgetComponent> HealthBar;

	
};
