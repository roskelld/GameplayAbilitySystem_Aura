// Copyright Iron Goblin Corp. 2023


#include "Character/AuraEnemy.h"
#include "Engine/Engine.h"
#include "Kismet/KismetSystemLibrary.h"

void AAuraEnemy::HighlightActor()
{
	bHighlighted = true;
	FString ActorDisplayName = GetOwner()->GetName();
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(100, 999.f, FColor::Blue, FString::Printf(TEXT("%s"), *ActorDisplayName));
}

void AAuraEnemy::UnHighlightActor()
{
	bHighlighted = false;
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(100, 999.f, FColor::Blue, TEXT(""));
}
