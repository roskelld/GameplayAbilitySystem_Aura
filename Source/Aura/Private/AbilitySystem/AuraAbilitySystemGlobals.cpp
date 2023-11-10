// Copyright Iron Goblin Corp. 2023


#include "AbilitySystem/AuraAbilitySystemGlobals.h"
#include "AuraAbilityTypes.h"

FGameplayEffectContext* UAuraAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAuraGameplayEffectContext();
}
