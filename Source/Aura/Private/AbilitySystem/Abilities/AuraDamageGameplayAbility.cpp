// Copyright Iron Goblin Corp. 2023


#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystemBlueprintLibrary.h>

void UAuraDamageGameplayAbility::CauseDamage(AActor* TargetActor)
{
	// Prep a Spec Handle to applye
	FGameplayEffectSpecHandle DamageSpecHandle = MakeOutgoingGameplayEffectSpec(DamageEffectClass, 1.f);

	// Loop over each damage type on the ability
	for (TTuple<FGameplayTag, FScalableFloat> Pair : DamageTypes)
	{
		// Get the damage value (probably from a curve table set on the ability)
		const float ScaledDamage = Pair.Value.GetValueAtLevel(GetAbilityLevel());

		// Assign the damage value and type to the spec handle
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(DamageSpecHandle, Pair.Key, ScaledDamage);
	}

	GetAbilitySystemComponentFromActorInfo()->ApplyGameplayEffectSpecToTarget(*DamageSpecHandle.Data.Get(), UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));
}
