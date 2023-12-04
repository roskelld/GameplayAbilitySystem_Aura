// Copyright Iron Goblin Corp. 2023


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystemBlueprintLibrary.h>

void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	// Prep a Spec Handle to applye
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);

	// Get the damage value (probably from a curve table set on the ability)
	const float ScaledDamage = Damage.GetValueAtLevel(GetAbilityLevel());

	// Assign the damage value and type to the spec handle
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, DamageType, ScaledDamage);

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}

FDamageEffectParams UAuraDamageGameplayAbility::MakeDamageEffectParamsFromClassDefault(AActor* TargetActor) const
{
	FDamageEffectParams Params;

	Params.WorldContextObject = GetAvatarActorFromActorInfo();
	Params.DamageGameplayEffectClass = DamageEffectClass;
	Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	Params.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	Params.BaseDamage = Damage.GetValueAtLevel(GetAbilityLevel());
	Params.AbilityLevel = GetAbilityLevel();
	Params.DamageType = DamageType;
	Params.DebuffChance = DebuffChance;
	Params.DebuffDamage = DebuffDamage;
	Params.DebuffDuration = DebuffDuration;
	Params.DebuffFrequency = DebuffFrequency;
	Params.DeathImpulseMagnitude = DeathImpulseMagnitude;

	return Params;
}
