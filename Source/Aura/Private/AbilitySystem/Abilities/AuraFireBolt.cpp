// Copyright Iron Goblin Corp. 2023


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "Interaction/CombatInterface.h"
#include <AbilitySystem/AuraAbilitySystemLibrary.h>
#include "Actor/AuraProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

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
	const int32 EffectiveNumProjectiles = FMath::Min(NumProjectiles, GetAbilityLevel());
	TArray<FRotator> Rotations = UAuraAbilitySystemLibrary::EvenlySpreadRotators(Forward, FVector::UpVector, ProjectileSpread, EffectiveNumProjectiles);
	
	for (FRotator& Rot : Rotations)
	{
		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);
		SpawnTransform.SetRotation(Rot.Quaternion());

		// Prepare projectile actor ready for spawn
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
		Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefault();

		if (HomingTarget && HomingTarget->Implements<UCombatInterface>())
		{
			Projectile->ProjectileMovement->HomingTargetComponent = HomingTarget->GetRootComponent();
		}
		else
		{
			// This is a scene component on the AuraProjectile that will be garbage collected after this projectile is done
			// Note that the ProjectileMovement->HomingTargetComponent takes a weak pointer reference, which is why we need
			// to set this up to be garbage collected, else it won't
			Projectile->HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
			Projectile->HomingTargetSceneComponent->SetWorldLocation(ProjectileTargetLocation);
			Projectile->ProjectileMovement->HomingTargetComponent = Projectile->HomingTargetSceneComponent;
		}

		Projectile->ProjectileMovement->HomingAccelerationMagnitude = FMath::FRandRange(MinHomingAcceleration, MaxHomingAcceleration);
		Projectile->ProjectileMovement->bIsHomingProjectile = bLaunchHomingProjectiles;

		Projectile->FinishSpawning(SpawnTransform);
	}
}
