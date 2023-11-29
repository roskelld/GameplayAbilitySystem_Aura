// Copyright Iron Goblin Corp. 2023


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include <Player/AuraPlayerState.h>


void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	check(AttributeInfo);

	for (auto& Pair : GetAuraAS()->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value);
			}
		);
	}

	// Attribute Points Changed
	GetAuraPS()->OnAttributePointsChangedDelegate.AddLambda(
		[this](int32 NewAttributePoints) { AttributePointsChangedDelegate.Broadcast(NewAttributePoints); }
	);

	// Spell Points Changed
	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda(
		[this](int32 NewSpellPoints) { SpellPointsChangedDelegate.Broadcast(NewSpellPoints); }
	);
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	check(AttributeInfo);
	
	for (auto& Pair : GetAuraAS()->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value);
	}

	// Broadcast Initial Attribute and Spell Points
	AttributePointsChangedDelegate.Broadcast(GetAuraPS()->GetAttributePoints());
	SpellPointsChangedDelegate.Broadcast(AuraPlayerState->GetSpellPoints());
}

void UAttributeMenuWidgetController::UpgradeAttribute(const FGameplayTag& AttributeTag)
{
	GetAuraASC()->UpgradeAttribute(AttributeTag);
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}