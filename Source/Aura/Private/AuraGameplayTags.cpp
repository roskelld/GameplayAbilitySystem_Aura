// Copyright Iron Goblin Corp. 2023


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

/** Define and expose the gameplay tag "Movement.Mode.Walking" to other modules and code. */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Primary_Strength, "Attributes.Primary.Strength", "Increase physical damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Primary_Intelligence, "Attributes.Primary.Intelligence", "Increase magic damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Primary_Resilience, "Attributes.Primary.Resilience", "Armor and Armor Penetration");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Primary_Vigor, "Attributes.Primary.Vigor", "Increase health");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Vital_Health, "Attributes.Vital.Health", "Current Health");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Vital_Mana, "Attributes.Vital.Mana", "Current Magic");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_Armor, "Attributes.Secondary.Armor", "Reduces damage taken, improves Block Chance");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_ArmorPenetration, "Attributes.Secondary.ArmorPenetration", "Ignores Percentage of enemy Armor, increase Critical Hit Chance");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_BlockChance, "Attributes.Secondary.BlockChance", "Chance to cut incoming damage in half");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_CriticalHitChance, "Attributes.Secondary.CriticalHitChance", "Chance to double damage, and critical hit bonus");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_CriticalHitDamage, "Attributes.Secondary.CriticalHitDamage", "Bonus damage added when a critical hit is scored");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_CriticalHitResistance, "Attributes.Secondary.CriticalHitResistance", "Reduces Critical Hit Chance of attacking enemies");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_HealthRegeneration, "Attributes.Secondary.HealthRegeneration", "Amount of Health regenerated every second");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_ManaRegeneration, "Attributes.Secondary.ManaRegeneration", "Amount of Mana regenerated every second");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_MaxHealth, "Attributes.Secondary.MaxHealth", "Maximum amount of Health obtainable");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_MaxMana, "Attributes.Secondary.MaxMana", "Maximum amount of Mana obtainable");

/* Controller Input Tags */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_LMB, "InputTag.LMB", "Input Tag for Left Mouse Button");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_RMB, "InputTag.RMB", "Input Tag for Right Mouse Button");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_1, "InputTag.1", "Input Tag for 1 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_2, "InputTag.2", "Input Tag for 2 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_3, "InputTag.3", "Input Tag for 3 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_4, "InputTag.4", "Input Tag for 4 Key");

/* Set By Caller Tags */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage, "Damage", "Damage tag used by Set by Caller");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage_Fire, "Damage.Fire", "Fire Damage Type");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effects_HitReact, "Effects.HitReact", "Applied to characters are hit reacting");

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	GameplayTags.Attributes_Primary_Strength = TAG_Attributes_Primary_Strength;
	GameplayTags.Attributes_Primary_Intelligence = TAG_Attributes_Primary_Intelligence;
	GameplayTags.Attributes_Primary_Resilience = TAG_Attributes_Primary_Resilience;
	GameplayTags.Attributes_Primary_Vigor = TAG_Attributes_Primary_Vigor;
	GameplayTags.Attributes_Vital_Health = TAG_Attributes_Vital_Health;
	GameplayTags.Attributes_Vital_Mana = TAG_Attributes_Vital_Mana;
	GameplayTags.Attributes_Secondary_Armor = TAG_Attributes_Secondary_Armor;
	GameplayTags.Attributes_Secondary_ArmorPenetration = TAG_Attributes_Secondary_ArmorPenetration;
	GameplayTags.Attributes_Secondary_BlockChance = TAG_Attributes_Secondary_BlockChance;
	GameplayTags.Attributes_Secondary_CriticalHitChance = TAG_Attributes_Secondary_CriticalHitChance;
	GameplayTags.Attributes_Secondary_CriticalHitDamage = TAG_Attributes_Secondary_CriticalHitDamage;
	GameplayTags.Attributes_Secondary_CriticalHitResistance = TAG_Attributes_Secondary_CriticalHitResistance;
	GameplayTags.Attributes_Secondary_HealthRegeneration = TAG_Attributes_Secondary_HealthRegeneration;
	GameplayTags.Attributes_Secondary_ManaRegeneration = TAG_Attributes_Secondary_ManaRegeneration;
	GameplayTags.Attributes_Secondary_MaxHealth = TAG_Attributes_Secondary_MaxHealth;
	GameplayTags.Attributes_Secondary_MaxMana = TAG_Attributes_Secondary_MaxMana;

	/* Controller Input Tags */
	GameplayTags.InputTag_LMB = TAG_InputTag_LMB;
	GameplayTags.InputTag_RMB = TAG_InputTag_RMB;
	GameplayTags.InputTag_1 = TAG_InputTag_1;
	GameplayTags.InputTag_2 = TAG_InputTag_2;
	GameplayTags.InputTag_3 = TAG_InputTag_3;
	GameplayTags.InputTag_4 = TAG_InputTag_4;

	/* Set By Caller Tags */
	GameplayTags.Damage = TAG_Damage;
	GameplayTags.Damage_Fire = TAG_Damage_Fire;

	// Array of all damage types
	GameplayTags.DamageTypes.Add(GameplayTags.Damage_Fire);

	GameplayTags.Effects_HitReact = TAG_Effects_HitReact;
}
