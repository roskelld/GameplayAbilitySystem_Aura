// Copyright Iron Goblin Corp. 2023

#include "AbilitySystem/AuraAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "AuraGameplayTags.h"
#include <Interaction/CombatInterface.h>
#include <Kismet/GameplayStatics.h>
#include <Player/AuraPlayerController.h>
#include <AbilitySystem/AuraAbilitySystemLibrary.h>
#include "AuraLogChannels.h"
#include <Interaction/PlayerInterface.h>
#include <AuraAbilityTypes.h>

UAuraAttributeSet::UAuraAttributeSet()
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

	// Primary Attributes
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Resilience, GetResilienceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute());

	// Secondary Attributes
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegeneration, GetHealthRegenerationAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegeneration, GetManaRegenerationAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute());

	// Resistance Attributes
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Fire, GetFireResistanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Lightning, GetLightningResistanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Arcane, GetArcaneResistanceAttribute());
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Physical, GetPhysicalResistanceAttribute());
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength,				COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor,				COND_None, REPNOTIFY_Always);
	
	// Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor,				COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, BlockChance,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance,	COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage,	COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance,COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, HealthRegeneration,	COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ManaRegeneration,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth,			COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana,				COND_None, REPNOTIFY_Always);

	// Resistance Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, FireResistance,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, LightningResistance,	COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArcaneResistance,		COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, PhysicalResistance,	COND_None, REPNOTIFY_Always);

	// Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health,				COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana,					COND_None, REPNOTIFY_Always);
}

// As per Epic's statement, this function is primarily used to clamp values 
// It shouldn't be used for any major value calculations.
// This will only forward the clamped value, it will not set the base value
// That can be done in post PostGameplayEffectExecute
void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxHealth());
	}

	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0, GetMaxMana());
	}
}

// Fills out a custom struct with source and target information that will
// be useful to access when dealing with GameplayEffects
// When using the resulting struct members should first be checked to see
// if they're populated as some GE's won't have all data
void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect
	// Target = target of the effect & owner of this AS

	Props.EffectContextHandle = Data.EffectSpec.GetContext();

	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}

		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		// There are many different ways to get the same data in GAS
		// Below showcases some examples of tapping the target data
		// and getting the value as well as using the BlueprintLibrary
		// functions to get.
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UAuraAttributeSet::ShowFloatingText(const FEffectProperties& Props, float Damage, bool bBlockedHit, bool bCriticalHit) const
{
	// Only show damage if it wasn't self inflicted
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		// Get Player Controller of damage source character
		// Server has access to all controllers, so returning the controller as it's called on the server
		// will direct us to the controlling player.
		if (AAuraPlayerController* PC = Cast<AAuraPlayerController>(Props.SourceCharacter->Controller))
		{
			// Show damage over damage target character
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCriticalHit);
			return;
		}

		// If the damage is coming to the player, then get the PC from the Target and show floating text on 
		// the player character
		if (AAuraPlayerController* PC = Cast<AAuraPlayerController>(Props.TargetCharacter->Controller))
		{
			// Show damage over damage target character
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bBlockedHit, bCriticalHit);
		}
	}
}

void UAuraAttributeSet::SendXPEvent(const FEffectProperties& Props)
{
	if (Props.TargetCharacter->Implements<UCombatInterface>())
	{
		const int32 TargetLevel = ICombatInterface::Execute_GetPlayerLevel(Props.TargetCharacter);
		// Note: When calling Blueprint Native events in C++ you need to call their Execute_ version as below
		const ECharacterClass TargetClass = ICombatInterface::Execute_GetCharacterClass(Props.TargetCharacter);
		const int32 XPReward = UAuraAbilitySystemLibrary::GetXPRewardForClassAndLevel(Props.TargetCharacter, TargetClass, TargetLevel);

		const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
		FGameplayEventData Payload;
		Payload.EventTag = GameplayTags.Attributes_Meta_IncomingXP;
		Payload.EventMagnitude = XPReward;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Props.SourceCharacter, GameplayTags.Attributes_Meta_IncomingXP, Payload);
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	// Block any further effects if character is dead 
	if (Props.TargetCharacter->Implements<UCombatInterface>() && ICombatInterface::Execute_IsDead(Props.TargetCharacter)) return;

	// Update Health
	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));

	// Update Mana
	if (Data.EvaluatedData.Attribute == GetManaAttribute()) SetMana(FMath::Clamp(GetMana(), 0, GetMaxMana()));

	// Meta Attribute Calculation for Incoming Damage
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		HandleIncomingDamage(Props);
	}

	// Meta Attribute Calculation for Incoming XP
	if (Data.EvaluatedData.Attribute == GetIncomingXPAttribute())
	{
		HandleIncomingXP(Props);
	}
}

void UAuraAttributeSet::HandleIncomingDamage(const FEffectProperties& Props)
{
	// Get current incoming damage
	const float LocalIncomingDamage = GetIncomingDamage();

	// Reset incoming damage
	SetIncomingDamage(0.f);

	// Do we need to calculate anything?
	if (LocalIncomingDamage > 0.f)
	{
		const float NewHealth = GetHealth() - LocalIncomingDamage;
		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

		const bool bFatal = (NewHealth <= 0.f);
		if (bFatal)
		{
			ICombatInterface* CombatInterface = Cast<ICombatInterface>(Props.TargetAvatarActor);
			if (CombatInterface)
			{
				CombatInterface->Die(UAuraAbilitySystemLibrary::GetDeathImpulse(Props.EffectContextHandle));
			}
			SendXPEvent(Props);
		}
		else
		{	
			// If not being shocked, then can hit react
			if (Props.TargetCharacter->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsBeingShocked(Props.TargetCharacter))
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FAuraGameplayTags::Get().Effects_HitReact);
				Props.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}

			const FVector& KnockbackForce = UAuraAbilitySystemLibrary::GetKnockbackForce(Props.EffectContextHandle);
			// Set Knockback effect
			if (!KnockbackForce.IsNearlyZero(1.f))
			{
				Props.TargetCharacter->LaunchCharacter(KnockbackForce, true, true);
			}

		}

		const bool bBlock = UAuraAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle);
		const bool bCriticalHit = UAuraAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
		ShowFloatingText(Props, LocalIncomingDamage, bBlock, bCriticalHit);
		if (UAuraAbilitySystemLibrary::IsSuccessfulDebuff(Props.EffectContextHandle))
		{
			// Handle Debuff
			Debuff(Props);
		}
	}
}

void UAuraAttributeSet::HandleIncomingXP(const FEffectProperties& Props)
{
	// Get current incoming XP
	const float LocalIncomingXP = GetIncomingXP();

	// Reset incoming XP
	SetIncomingXP(0.f);

	if (LocalIncomingXP > 0.f && Props.SourceCharacter->Implements<UPlayerInterface>() && Props.SourceCharacter->Implements<UCombatInterface>())
	{
		const int32 CurrentLevel = ICombatInterface::Execute_GetPlayerLevel(Props.SourceCharacter);
		const int32 CurrentXP = IPlayerInterface::Execute_GetXP(Props.SourceCharacter);


		const int32 NewLevel = IPlayerInterface::Execute_FindLevelForXP(Props.SourceCharacter, CurrentXP + LocalIncomingXP);
		const int32 NumLevelUps = NewLevel - CurrentLevel;

		if (NumLevelUps > 0)
		{
			const int32 AttributePointsReward = IPlayerInterface::Execute_GetAttributePointsReward(Props.SourceCharacter, NewLevel);
			const int32 SpellPointsReward = IPlayerInterface::Execute_GetSpellPointsReward(Props.SourceCharacter, NewLevel);

			IPlayerInterface::Execute_AddToPlayerLevel(Props.SourceCharacter, NumLevelUps);
			IPlayerInterface::Execute_AddToAttributePoints(Props.SourceCharacter, AttributePointsReward);
			IPlayerInterface::Execute_AddToSpellPoints(Props.SourceCharacter, SpellPointsReward);

			// Fill up Health and Mana
			// Don't update here because the level up hasn't executed yet and won't fill up to
			// new max values. Instead it is done PostAttributeChange.
			bTopOffHealth = true;
			bTopoffMana = true;

			IPlayerInterface::Execute_LevelUp(Props.SourceCharacter);
		}
		IPlayerInterface::Execute_AddToXP(Props.SourceCharacter, LocalIncomingXP);
	}
}

void UAuraAttributeSet::Debuff(const FEffectProperties& Props)
{
	const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();

	FGameplayEffectContextHandle EffectContext = Props.SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(Props.SourceCharacter);

	const FGameplayTag DamageType = UAuraAbilitySystemLibrary::GetDamageType(Props.EffectContextHandle);
	const float DebuffDamage = UAuraAbilitySystemLibrary::GetDebuffDamage(Props.EffectContextHandle);
	const float DebuffDuration = UAuraAbilitySystemLibrary::GetDebuffDuration(Props.EffectContextHandle);
	const float DebuffFrequency = UAuraAbilitySystemLibrary::GetDebuffFrequency(Props.EffectContextHandle);

	FString DebuffName = FString::Printf(TEXT("DynamicDebuff_%s"), *DamageType.ToString());

	// Make a Dynamic Gameplay Effect!
	// NOTE: Not suited for Replication so must be handled on the server
	// Any attribute that IS replicated will work as they use their own replication
	// Meta attributes are not replicated, so this could be a problem unless their driving
	// attribute IS replicated, and really they should be.
	UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage(), FName(DebuffName));

	Effect->DurationPolicy = EGameplayEffectDurationType::HasDuration;
	Effect->Period = DebuffFrequency;
	Effect->DurationMagnitude = FScalableFloat(DebuffDuration);

	const FGameplayTag DebuffTag = Tags.DamageTypesToDebuffs[DamageType];
	Effect->InheritableOwnedTagsContainer.AddTag(DebuffTag);

	// If Player is stunned block all input
	if (DebuffTag.MatchesTagExact(Tags.Debuff_Stun))
	{
		Effect->InheritableOwnedTagsContainer.AddTag(Tags.Player_Block_CursorTrace);
		Effect->InheritableOwnedTagsContainer.AddTag(Tags.Player_Block_InputHeld);
		Effect->InheritableOwnedTagsContainer.AddTag(Tags.Player_Block_InputPressed);
		Effect->InheritableOwnedTagsContainer.AddTag(Tags.Player_Block_InputReleased);
	}

	Effect->StackingType = EGameplayEffectStackingType::AggregateBySource;
	Effect->StackLimitCount = 1;

	// Only adding one modifier in this but by index++ you can add more
	const int32 index = Effect->Modifiers.Num();
	Effect->Modifiers.Add(FGameplayModifierInfo());
	FGameplayModifierInfo& ModifierInfo = Effect->Modifiers[index];

	ModifierInfo.ModifierMagnitude = FScalableFloat(DebuffDamage);
	ModifierInfo.ModifierOp = EGameplayModOp::Additive;
	ModifierInfo.Attribute = UAuraAttributeSet::GetIncomingDamageAttribute();

	if (const FGameplayEffectSpec* MutableSpec = new FGameplayEffectSpec(Effect, EffectContext, 1.f))
	{
		FAuraGameplayEffectContext *AuraContext = static_cast<FAuraGameplayEffectContext*>(MutableSpec->GetContext().Get());
		TSharedPtr<FGameplayTag> DebuffDamageType = MakeShareable(new FGameplayTag(DamageType));
		AuraContext->SetDamageType(DebuffDamageType);

		// Apply the effect
		Props.TargetASC->ApplyGameplayEffectSpecToSelf(*MutableSpec);
	}
}

void UAuraAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeBaseChange(Attribute, OldValue, NewValue);


	if (Attribute == GetMaxHealthAttribute() && bTopOffHealth)
	{
		SetHealth(GetMaxHealth());
		bTopOffHealth = false;
	}
	if (Attribute == GetMaxManaAttribute() && bTopoffMana)
	{
		SetMana(GetMaxMana());
		bTopoffMana = false;
	}
}

/* Vital OnRep Functions */

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

/* Primary OnRep Functions */

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

/* Secondary OnRep Functions */

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, BlockChance, OldBlockChance);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, CriticalHitResistance);
}

void UAuraAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void UAuraAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ManaRegeneration, OldManaRegeneration);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::OnRep_FireResistance(const FGameplayAttributeData& OldFireResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, FireResistance, OldFireResistance);
}

void UAuraAttributeSet::OnRep_LightningResistance(const FGameplayAttributeData& OldLightningResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, LightningResistance, OldLightningResistance);
}

void UAuraAttributeSet::OnRep_ArcaneResistance(const FGameplayAttributeData& OldArcaneResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArcaneResistance, OldArcaneResistance);
}

void UAuraAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, PhysicalResistance, OldPhysicalResistance);
}


