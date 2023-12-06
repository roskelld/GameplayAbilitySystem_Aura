// Copyright Iron Goblin Corp. 2023


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "Interaction/CombatInterface.h"
#include <AbilitySystem/AuraAbilitySystemLibrary.h>
#include "Actor/AuraProjectile.h"

FString UAuraFireBolt::GetDescription(int32 Level)
{
	const int32 CurrentProjectileCount = FMath::Min(Level, NumProjectiles);
	const int32 ScaledDamage = Damage.GetValueAtLevel(Level);
	const float ManaCost = GetManaCost(Level);
	const float Cooldown = GetCooldown(Level);
	if (Level == 1)
	{
		return FString::Printf(TEXT(
			// Spell Title
			"<Title>FIRE BOLT</>\n"

			// Details
			"<Small>Level: </><Level>%d</>\n"
			"<Small>ManaCost: </><ManaCost>%.1f</>\n"
			"<Small>Cooldown: </><Cooldown>%.1f</>\n"

			// Description & Damage
			"<Default>Launches a bolt of fire, exploding on impact and dealing: </>"
			"<Damage>%d</><Default> fire damage with a chance to burn.</>"), 

			// Values
			Level,
			ManaCost,
			Cooldown,
			ScaledDamage);
	}
	return FString::Printf(TEXT(
		// Spell Title
		"<Title>FIRE BOLT</>\n"

		// Details
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n"

		// Description & Damage
		"<Default>Launches %d bolts of fire, exploding on impact and dealing: </>"
		"<Damage>%d</><Default> fire damage with a chance to burn.</>"),

		// Values
		Level,
		ManaCost,
		Cooldown,
		CurrentProjectileCount,
		ScaledDamage);
}

FString UAuraFireBolt::GetNextLevelDescription(int32 NextLevel)
{
	const int32 CurrentProjectileCount = FMath::Min(NextLevel, NumProjectiles);
	const int32 ScaledDamage = Damage.GetValueAtLevel(NextLevel);
	const float ManaCost = GetManaCost(NextLevel);
	const float Cooldown = GetCooldown(NextLevel);

	return FString::Printf(TEXT(
		// Spell Title
		"<Title>NEXT LEVEL:</>\n"

		// Details
		"<Small>Level: </><Level>%d</>\n"
		"<Small>ManaCost: </><ManaCost>%.1f</>\n"
		"<Small>Cooldown: </><Cooldown>%.1f</>\n"

		// Description & Damage
		"<Default>Launches %d bolts of fire, exploding on impact and dealing: </>"
		"<Damage>%d</><Default> fire damage with a chance to burn.</>"),

		// Values
		NextLevel,
		ManaCost,
		Cooldown,
		CurrentProjectileCount,
		ScaledDamage);
}

void UAuraFireBolt::SpawnProjectiles(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, bool bOverridePitch, float PitchOverride, AActor* HomingTarget)
{
	// Check that we have authority over this ability 
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

	// Exit if we are not the server
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(GetAvatarActorFromActorInfo(), SocketTag);
	FRotator Rotation = (ProjectileTargetLocation - SocketLocation).Rotation();
	if (bOverridePitch) Rotation.Pitch = PitchOverride;

	const FVector Forward = Rotation.Vector();
	TArray<FRotator> Rotations = UAuraAbilitySystemLibrary::EvenlySpreadRotators(Forward, FVector::UpVector, ProjectileSpread, NumProjectiles);
	
	for (FRotator& Rot : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());

		// Prepare projectile actor ready for spawn
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefault();

		Projectile->FinishSpawning(SpawnTransform);
	}

}
