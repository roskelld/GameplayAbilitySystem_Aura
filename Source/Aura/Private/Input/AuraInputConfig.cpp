// Copyright Iron Goblin Corp. 2023


#include "Input/AuraInputConfig.h"
#include <EnhancedInputLibrary.h>

const UInputAction* UAuraInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FAuraInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag) return Action.InputAction;
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s], on InputConfig"), *InputTag.ToString(), *GetNameSafe(this));
	}
	
	return nullptr;
}
