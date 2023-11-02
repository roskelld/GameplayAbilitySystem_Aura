// Copyright Iron Goblin Corp. 2023


#include "AuraAssetManager.h"
#include "AuraGameplayTags.h"
#include "AbilitySystemGlobals.h"

UAuraAssetManager& UAuraAssetManager::Get()
{
	check(GEngine);

	UAuraAssetManager* AuraAssetManager = Cast<UAuraAssetManager>(GEngine->AssetManager);

	return *AuraAssetManager;
}

void UAuraAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FAuraGameplayTags::InitializeNativeGameplayTags();

	// Required for Target Data (for projectiles)
	// clients will yolo into their own instance if not.
	// Can be removed in UE 5.3 as it's not needed
	UAbilitySystemGlobals::Get().InitGlobalData();
}
