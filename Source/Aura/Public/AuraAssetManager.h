// Copyright Iron Goblin Corp. 2023

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "AuraAssetManager.generated.h"

/**
 * Project's custom Asset Manager
 * MUST be added to the config/DefaultEngine.ini
 * Under section: 
 * [/Script/Engine.Engine]
 * AssetManagerClassName=/Script/Aura.AuraAssetManager
 * NOTE: Make sure there's a new line at the end 
 * or the engine won't see the entry.
 */
UCLASS()
class AURA_API UAuraAssetManager : public UAssetManager
{
	GENERATED_BODY()
public:
	static UAuraAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
	
};
