// Copyright Iron Goblin Corp. 2023

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;

protected:

	/* 
	 Broadcast event messages via Tags
	 Using the GameplayEffectAssetTags (Added in the GE) we can broadcast them to any associated deligate
	 such as UI widgets, so they can display appropreate user updates.
	 The useful concept here is that these tags are not applied to the character, but stay on the GE, *and*
	 they work on instant effects too, sending the tag out before removing it. So great for flash events. 
	*/
	void EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

};
