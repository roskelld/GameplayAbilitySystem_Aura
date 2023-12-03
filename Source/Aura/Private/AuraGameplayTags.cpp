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

/* Resistances */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Resistance_Fire, "Attributes.Resistance.Fire", "Resistance to Fire Damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Resistance_Lightning, "Attributes.Resistance.Lightning", "Resistance to Lightning Damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Resistance_Arcane, "Attributes.Resistance.Arcane", "Resistance to Arcane Damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Resistance_Physical, "Attributes.Resistance.Physical", "Resistance to Physical Damage");

/* Debuffs */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Burn, "Debuff.Burn", "Debuff to Fire damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Stun, "Debuff.Stun", "Debuff to Lightning damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Arcane, "Debuff.Arcane", "Debuff to Arcane damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Physical, "Debuff.Physical", "Debuff to Physical damage");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Chance, "Debuff.Chance", "Chance to Debuff");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Damage, "Debuff.Damage", "Debuff damage");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Duration, "Debuff.Duration", "Length of time for Debuff");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Debuff_Frequency, "Debuff.Frequency", "How often can Debuff happen");

/* Meta Attributes */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Attributes_Meta_IncomingXP, "Attributes.Meta.IncomingXP", "Incoming XP Reward");

/* Controller Input Tags */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_LMB, "InputTag.LMB", "Input Tag for Left Mouse Button");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_RMB, "InputTag.RMB", "Input Tag for Right Mouse Button");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_1, "InputTag.1", "Input Tag for 1 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_2, "InputTag.2", "Input Tag for 2 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_3, "InputTag.3", "Input Tag for 3 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_4, "InputTag.4", "Input Tag for 4 Key");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_Passive_1, "InputTag.Passive.1", "Input Tag for Passive 1");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_InputTag_Passive_2, "InputTag.Passive.2", "Input Tag for Passive 2");

/* Set By Caller Tags */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage, "Damage", "Damage tag used by Set by Caller");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage_Fire, "Damage.Fire", "Fire Damage Type");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage_Lightning, "Damage.Lightning", "Lightning Damage Type");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage_Arcane, "Damage.Arcane", "Arcane Damage Type");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Damage_Physical, "Damage.Physical", "Physical Damage Type");

UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Effects_HitReact, "Effects.HitReact", "Applied to characters are hit reacting");

/* Ability Style */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Attack, "Abilities.Attack", "Attack ability");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Summon, "Abilities.Summon", "Summon ability");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_HitReact, "Abilities.HitReact", "Applied to characters are hit reacting");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_None, "Abilities.None", "No Ability - nullptr for Abilities");

/* Ability Eligibility Status */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Status_Locked, "Abilities.Status.Locked", "Ability is locked");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Status_Eligible, "Abilities.Status.Eligible", "Ability is eligible to be unlocked");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Status_Unlocked, "Abilities.Status.Unlocked", "Ability is unlocked");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Status_Equipped, "Abilities.Status.Equipped", "Ability is equipped");

/* Ability Type */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Type_Offensive, "Abilities.Type.Offensive", "Offensive ability");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Type_Passive, "Abilities.Type.Passive", "Passive ability");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Type_None, "Abilities.Type.None", "Ability has no set type");

/* Ability */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Fire_FireBolt, "Abilities.Fire.FireBolt", "FireBolt ability");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Abilities_Lightning_Electrocute, "Abilities.Lightning.Electrocute", "Electrocute ability");

/* Cooldowns */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Cooldown_Fire_FireBolt, "Cooldown.Fire.FireBolt", "FireBolt ability Cooldown");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Cooldown_Lightning_Electrocute, "Cooldown.Lightning.Electrocute", "Electrocute ability Cooldown");

/* Sockets */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_CombatSocket_Weapon, "CombatSocket.Weapon", "Weapon Combat Socket");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_CombatSocket_RightHand, "CombatSocket.RightHand", "Right Hand Combat Socket");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_CombatSocket_LeftHand, "CombatSocket.LeftHand", "Left Hand Combat Socket");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_CombatSocket_Tail, "CombatSocket.Tail", "Tail Combat Socket");

/* Montages */
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Montage_Attack_1, "Montage.Attack.1", "Attack Montage 1");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Montage_Attack_2, "Montage.Attack.2", "Attack Montage 2");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Montage_Attack_3, "Montage.Attack.3", "Attack Montage 3");
UE_DEFINE_GAMEPLAY_TAG_COMMENT(TAG_Montage_Attack_4, "Montage.Attack.4", "Attack Montage 4");

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
	GameplayTags.InputTag_Passive_1 = TAG_InputTag_Passive_1;
	GameplayTags.InputTag_Passive_2 = TAG_InputTag_Passive_2;

	/* Set By Caller Tags */
	GameplayTags.Damage = TAG_Damage;

	/* 
	 *	Damage Types
	 */
	GameplayTags.Damage_Fire = TAG_Damage_Fire;
	GameplayTags.Damage_Lightning = TAG_Damage_Lightning;
	GameplayTags.Damage_Arcane = TAG_Damage_Arcane;
	GameplayTags.Damage_Physical = TAG_Damage_Physical;

	/*
	*	Meta
	*/
	GameplayTags.Attributes_Meta_IncomingXP = TAG_Attributes_Meta_IncomingXP;

	/*
	 *	Resistances
	 */
	GameplayTags.Attributes_Resistance_Fire = TAG_Attributes_Resistance_Fire;
	GameplayTags.Attributes_Resistance_Lightning = TAG_Attributes_Resistance_Lightning;
	GameplayTags.Attributes_Resistance_Arcane = TAG_Attributes_Resistance_Arcane;
	GameplayTags.Attributes_Resistance_Physical = TAG_Attributes_Resistance_Physical;

	/*
	 *	Map of Damage Types to Resistances
	 */
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);

	/*
	 *	Debuffs
	 */
	GameplayTags.Debuff_Burn = TAG_Debuff_Burn;
	GameplayTags.Debuff_Stun = TAG_Debuff_Stun;
	GameplayTags.Debuff_Arcane = TAG_Debuff_Arcane;
	GameplayTags.Debuff_Physical = TAG_Debuff_Physical;

	GameplayTags.Debuff_Chance = TAG_Debuff_Chance;
	GameplayTags.Debuff_Damage = TAG_Debuff_Damage;
	GameplayTags.Debuff_Duration = TAG_Debuff_Duration;
	GameplayTags.Debuff_Frequency = TAG_Debuff_Frequency;

	/*
	 *	Map of Damage Types to Debuffs
	 */
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Fire, GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Lightning, GameplayTags.Debuff_Stun);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Arcane, GameplayTags.Debuff_Arcane);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Physical, GameplayTags.Debuff_Physical);

	/*
	 *	Effects
	 */
	GameplayTags.Effects_HitReact = TAG_Effects_HitReact;

	/*
	 *	Ability Style
	 */
	GameplayTags.Abilities_Attack = TAG_Abilities_Attack;
	GameplayTags.Abilities_Summon = TAG_Abilities_Summon;
	GameplayTags.Abilities_HitReact = TAG_Abilities_HitReact;
	GameplayTags.Abilities_None = TAG_Abilities_None;

	/* 
	*	Ability Eligibility Status 
	*/
	GameplayTags.Abilities_Status_Locked = TAG_Abilities_Status_Locked;
	GameplayTags.Abilities_Status_Eligible = TAG_Abilities_Status_Eligible;
	GameplayTags.Abilities_Status_Unlocked = TAG_Abilities_Status_Unlocked;
	GameplayTags.Abilities_Status_Equipped = TAG_Abilities_Status_Equipped;

	/*
	*	Ability Type
	*/
	GameplayTags.Abilities_Type_Offensive = TAG_Abilities_Type_Offensive;
	GameplayTags.Abilities_Type_Passive = TAG_Abilities_Type_Passive;
	GameplayTags.Abilities_Type_None = TAG_Abilities_Type_None;

	/*
	*	Ability
	*/
	GameplayTags.Abilities_Fire_FireBolt = TAG_Abilities_Fire_FireBolt;
	GameplayTags.Abilities_Lightning_Electrocute = TAG_Abilities_Lightning_Electrocute;

	/*
	*	Cooldowns
	*/

	GameplayTags.Cooldown_Fire_FireBolt = TAG_Cooldown_Fire_FireBolt;
	GameplayTags.Cooldown_Lightning_Electrocute = TAG_Cooldown_Lightning_Electrocute;

	/*
	*	Sockets
	*/

	GameplayTags.CombatSocket_Weapon = TAG_CombatSocket_Weapon;
	GameplayTags.CombatSocket_RightHand = TAG_CombatSocket_RightHand;
	GameplayTags.CombatSocket_LeftHand = TAG_CombatSocket_LeftHand;
	GameplayTags.CombatSocket_Tail = TAG_CombatSocket_Tail;

	/*
	*	Montage
	*/

	GameplayTags.Montage_Attack_1 = TAG_Montage_Attack_1;
	GameplayTags.Montage_Attack_2 = TAG_Montage_Attack_2;
	GameplayTags.Montage_Attack_3 = TAG_Montage_Attack_3;
	GameplayTags.Montage_Attack_4 = TAG_Montage_Attack_4;
}
