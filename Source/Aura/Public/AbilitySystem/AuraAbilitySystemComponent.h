// Copyright Iron Goblin Corp. 2023

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AuraAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer& /*AssetTags*/);
DECLARE_MULTICAST_DELEGATE(FAbilitiesGiven);
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);
DECLARE_MULTICAST_DELEGATE_ThreeParams(FAbilityStatusChanged, const FGameplayTag& /* AbilityTag */, const FGameplayTag& /* StatusTag */, int32 /*AbilityLevel*/);

/**
 * 
 */
UCLASS()
class AURA_API UAuraAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void AbilityActorInfoSet();

	// Delegates
	FEffectAssetTags EffectAssetTags;
	FAbilitiesGiven AbilitiesGivenDelegate;
	FAbilityStatusChanged AbilityStatusChanged;

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupAbilities);
	void AddCharacterPassiveAbilities(const TArray<TSubclassOf<UGameplayAbility>>& StartupPassiveAbilities);
	bool bStartupAbilitiesGiven = false;

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);

	// Runs over each activatable ability and adds a delegate that can
	// be called to broadcast to those that subscribe, which will be the UI
	// looking for input, tags, icons.
	void ForEachAbility(const FForEachAbility& Delegate);

	static FGameplayTag GetAbilityTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);
	static FGameplayTag GetInputTagFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	// Get the current status of an ability from its ability spec
	static FGameplayTag GetStatusFromSpec(const FGameplayAbilitySpec& AbilitySpec);

	FGameplayAbilitySpec* GetSpecFromAbilityTag(const FGameplayTag& AbilityTag);

	// This routes through to GA_ListenForEvents that takes in AttributeTags and runs GE_EventBasedEffect
	// The modifiers are AttributeBased linked to the AttributeTag and updates attributes on SetByCaller
	// Works for Attributes and XP 
	void UpgradeAttribute(const FGameplayTag& AttributeTag);

	// NOTE: Server based functions must be implementated with the _Implementation naming convention
	UFUNCTION(Server, Reliable)
	void ServerUpgradeAttribute(const FGameplayTag& AttributeTag);

	// Update ability based on character level
	void UpdateAbilityStatuses(int32 Level);

	// NOTE: Server based functions must be implementated with the _Implementation naming convention
	UFUNCTION(Server, Reliable)
	void Server_SpendSpellPoint(const FGameplayTag& AbilityTag);

protected:

	// Replicate to the clients the activatable abilities so they can run the deletgates and update UI
	virtual void OnRep_ActivateAbilities() override;

	/* 
	 Broadcast event messages via Tags
	 Using the GameplayEffectAssetTags (Added in the GE) we can broadcast them to any associated deligate
	 such as UI widgets, so they can display appropreate user updates.
	 The useful concept here is that these tags are not applied to the character, but stay on the GE, *and*
	 they work on instant effects too, sending the tag out before removing it. So great for flash events. 
	*/
	UFUNCTION(Client, Reliable)
	void ClientEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

	UFUNCTION(Client, Reliable)
	void ClientUpdateAbilityStatus(const FGameplayTag& AbilityTag, const FGameplayTag& StatusTag, int32 AbilityLevel);
};
