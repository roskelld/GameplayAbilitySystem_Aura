// Copyright Iron Goblin Corp. 2023


#include "UI/WidgetController/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include <AbilitySystem/AuraAbilitySystemComponent.h>
#include "AbilitySystem/Data/LevelUpInfo.h"
#include <Player/AuraPlayerState.h>

void UOverlayWidgetController::BroadcastInitialValues()
{
	OnHealthChanged.Broadcast(GetAuraAS()->GetHealth());
	OnMaxHealthChanged.Broadcast(GetAuraAS()->GetMaxHealth());
	OnManaChanged.Broadcast(GetAuraAS()->GetMana());
	OnMaxManaChanged.Broadcast(GetAuraAS()->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{

	// XP Changed
	GetAuraPS()->OnXPChangedDelegate.AddUObject(this, &UOverlayWidgetController::OnXPChanged);

	// Level Changed
	// Bind to the PlayerState Level Changed and broadcast it through the widget
	GetAuraPS()->OnLevelChangedDelegate.AddLambda(
		[this](int32 NewLevel) { OnPlayerLevelChangedDelegate.Broadcast(NewLevel);}
	);

	// Attribute Points Changed
	GetAuraPS()->OnAttributePointsChangedDelegate.AddLambda(
		[this](int32 NewAttributePoints) { OnAttributePointsChangedDelegate.Broadcast(NewAttributePoints); }
	);

	// Spell Points Changed
	GetAuraPS()->OnSpellPointsChangedDelegate.AddLambda(
		[this](int32 NewSpellPoints) { OnSpellPointsChangedDelegate.Broadcast(NewSpellPoints); }
	);

	// This binds the value changes to the local function calls as part of GAS
	// Uses Lambda rather than bind to a local function 
	// see: https://github.com/roskelld/GameplayAbilitySystem_Aura/commit/9f47b6ee33f568b1d715edb868418fea953fb60a
	// For older version of set up.
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) { OnHealthChanged.Broadcast(Data.NewValue); }
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) { OnMaxHealthChanged.Broadcast(Data.NewValue); }
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) { OnManaChanged.Broadcast(Data.NewValue); }
	);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(GetAuraAS()->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data) { OnMaxManaChanged.Broadcast(Data.NewValue); }
	);

	// Use Lambda function - unnamed [] function that binds to the broadcast of EffectAssetTags in 
	// UAuraAbilitySystemComponent

	if (GetAuraASC())
	{
		if (GetAuraASC()->bStartupAbilitiesGiven)
		{
			BroadcastAbilityInfo();
		}
		else 
		{
			GetAuraASC()->AbilitiesGivenDelegate.AddUObject(this, &UOverlayWidgetController::BroadcastAbilityInfo);
		}
		

		GetAuraASC()->EffectAssetTags.AddLambda(
			[this](const FGameplayTagContainer& AssetTags)
			{
				for (const FGameplayTag& Tag : AssetTags)
				{
					// Example of how Tags are understood
					// Example: Tag = Message.HealthPotion
					// "Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
					FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));

					// Only broadcast to widget if we find a "Message" based row
					if (Tag.MatchesTag(MessageTag))
					{
						const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
						MessageWidgetRowDelegate.Broadcast(*Row);
					}
				}
			}
		);
	}
}

void UOverlayWidgetController::OnXPChanged(int32 NewXP)
{
	const ULevelUpInfo* LevelUpInfo = GetAuraPS()->LevelUpInfo;
	checkf(LevelUpInfo, TEXT("Unable to find Level Information, Please fill out PlayerState information"));

	int32 Level = LevelUpInfo->FindLevelForXP(NewXP);

	const int32 MaxLevel = LevelUpInfo->LevelUpInformation.Num();

	if (Level <= MaxLevel && Level > 0)
	{
		const int32 LevelUpRequirement = LevelUpInfo->LevelUpInformation[Level].LevelUpRequirement;
		const int32 PreviousLevelRequirement = LevelUpInfo->LevelUpInformation[Level - 1].LevelUpRequirement;
		
		const int32 DeltaLevelRequirement = LevelUpRequirement - PreviousLevelRequirement;

		const int32 XPForThisLevel = NewXP - PreviousLevelRequirement;

		const float XPBarPercent = static_cast<float>(XPForThisLevel) / static_cast<float>(DeltaLevelRequirement);
		
		OnXPPercentChangedDelegate.Broadcast(XPBarPercent);
	}
}
