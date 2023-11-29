// Copyright Iron Goblin Corp. 2023


#include "UI/WidgetController/AuraWidgetController.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Player/AuraPlayerState.h"
#include "Player/AuraPlayerController.h"

void UAuraWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UAuraWidgetController::BroadcastInitialValues()
{

}

void UAuraWidgetController::BindCallbacksToDependencies()
{
}

void UAuraWidgetController::BroadcastAbilityInfo()
{
	// Get Information about all given abilities, look up their Ability Info, and broadcast it to the widgets.
	if (!GetAuraASC()->bStartupAbilitiesGiven) return;

	// Create a lambda function that can be broadcast to subscritions in order to retrieve info 
	// This is implimented as a lambda but could be a function pointer as well. Many ways to skin a cat. 
	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this](const FGameplayAbilitySpec& AbilitySpec)
		{
			// Get the Ability info
			// FAuraAbilityInfo Info = FAuraAbilityInfo(); // AbilityInfo->FindAbilityInfoForTag(AuraASC->GetAbilityTagFromSpec(AbilitySpec));
			FAuraAbilityInfo Info = AbilityInfo->FindAbilityInfoForTag(AuraAbilitySystemComponent->GetAbilityTagFromSpec(AbilitySpec));
			// Add the input tag to it (abilities can be set to different input tags so this isn't part of the spec
			Info.InputTag = AuraAbilitySystemComponent->GetInputTagFromSpec(AbilitySpec);
			// Broadcast the info
			AbilityInfoDelegate.Broadcast(Info);
		});

	// Go through each ability and assign it the lambda delegate to be able to broadcast
	GetAuraASC()->ForEachAbility(BroadcastDelegate);
}

AAuraPlayerController* UAuraWidgetController::GetAuraPC()
{
	if (AuraPlayerController == nullptr)
	{
		AuraPlayerController = Cast<AAuraPlayerController>(PlayerController);
	}
	return AuraPlayerController;
}

AAuraPlayerState* UAuraWidgetController::GetAuraPS()
{
	if (AuraPlayerState == nullptr)
	{
		AuraPlayerState = Cast<AAuraPlayerState>(PlayerState);
	}
	return AuraPlayerState;
}

UAuraAbilitySystemComponent* UAuraWidgetController::GetAuraASC()
{
	if (AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent);
	}
	return AuraAbilitySystemComponent;
}

UAuraAttributeSet* UAuraWidgetController::GetAuraAS()
{
	if (AuraAttributeSet == nullptr)
	{
		AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	}
	return AuraAttributeSet;
}
