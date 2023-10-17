// Copyright Iron Goblin Corp. 2023

#include "Player/AuraPlayerState.h"

AAuraPlayerState::AAuraPlayerState()
{
	// Default update is slow for player state.
	// Using it with GAS requires higher update
	// to keep clients in sync
	NetUpdateFrequency = 100.f;
}