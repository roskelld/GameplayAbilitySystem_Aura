// Copyright Iron Goblin Corp. 2023


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

/** Define and expose the gameplay tag "Movement.Mode.Walking" to other modules and code. */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Primary_Strength, "Attributes.Primary.Strength", "Increase physical damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Primary_Intelligence, "Attributes.Primary.Intelligence", "Increase magic damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Primary_Resilience, "Attributes.Primary.Resilience", "Armor and Armor Penetration");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Primary_Vigor, "Attributes.Primary.Vigor", "Increase health");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Vital_Health, "Attributes.Vital.Health", "Health");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Vital_Mana, "Attributes.Vital.Mana", "Magic");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_Armor, "Attributes.Secondary.Armor", "Reduces damage taken, improves Block Chance");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_ArmorPenetration, "Attributes.Secondary.ArmorPenetration", "");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_BlockChance, "Attributes.Secondary.BlockChance", "");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_CriticalHitChance, "Attributes.Secondary.CriticalHitChance", "");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_CritialHitDamage, "Attributes.Secondary.CritialHitDamage", "");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_CritialHitResistance, "Attributes.Secondary.CritialHitResistance", "");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_HealthRegeneration, "Attributes.Secondary.HealthRegeneration", "");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_ManaRegeneration, "Attributes.Secondary.ManaRegeneration", "");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_MaxHealth, "Attributes.Secondary.MaxHealth", "");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Secondary_MaxMana, "Attributes.Secondary.MaxMana", "");

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
	GameplayTags.Attributes_Secondary_CritialHitDamage = TAG_Attributes_Secondary_CritialHitDamage;
	GameplayTags.Attributes_Secondary_CritialHitResistance = TAG_Attributes_Secondary_CritialHitResistance;
	GameplayTags.Attributes_Secondary_HealthRegeneration = TAG_Attributes_Secondary_HealthRegeneration;
	GameplayTags.Attributes_Secondary_ManaRegeneration = TAG_Attributes_Secondary_ManaRegeneration;
	GameplayTags.Attributes_Secondary_MaxHealth = TAG_Attributes_Secondary_MaxHealth;
	GameplayTags.Attributes_Secondary_MaxMana = TAG_Attributes_Secondary_MaxMana;
}
