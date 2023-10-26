// Copyright Iron Goblin Corp. 2023

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"

/** Primary Tags */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Strength)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Intelligence)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Resilience)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Primary_Vigor)

/** Vital Tags */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_Health)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Vital_Mana)

/** Secondary Tags */
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_Armor)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_ArmorPenetration)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_BlockChance)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_CriticalHitChance)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_CritialHitDamage)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_CritialHitResistance)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_HealthRegeneration)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_ManaRegeneration)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_MaxHealth)
UE_DECLARE_GAMEPLAY_TAG_EXTERN(TAG_Attributes_Secondary_MaxMana)

/**
 * AuraGameplayTags
 * 
 * Singleton containing native Gameplay Tags
 */

struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CritialHitDamage;
	FGameplayTag Attributes_Secondary_CritialHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegeneration;
	FGameplayTag Attributes_Secondary_ManaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	
protected:

private:
	static FAuraGameplayTags GameplayTags;
};