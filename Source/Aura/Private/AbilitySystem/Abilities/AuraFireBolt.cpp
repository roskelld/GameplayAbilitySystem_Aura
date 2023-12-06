// Copyright Iron Goblin Corp. 2023


#include "AbilitySystem/Abilities/AuraFireBolt.h"
#include "Interaction/CombatInterface.h"
#include <Kismet/KismetSystemLibrary.h>

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
	const FVector LeftOfSpread = Forward.RotateAngleAxis(-ProjectileSpread / 2.f, FVector::UpVector);
	const FVector RightOfSpread = Forward.RotateAngleAxis(ProjectileSpread / 2.f, FVector::UpVector);
	const FVector Start = SocketLocation + FVector(0, 0, 5.f);

	//NumProjectiles - FMath::Min(MaxNumProjectiles, GetAbilityLevel());

	if (NumProjectiles > 1)
	{
		const float DeltaSpread = ProjectileSpread / (NumProjectiles - 1);
		for (int32 i = 0; i < NumProjectiles; i++)
		{
			const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
			UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Start, Start + Direction * 75.f, 1, FLinearColor::Red, 120, 1);

		}
	} 
	else 
	{ 
		// Single Projectile
		UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), Start, Start + Forward * 75.f, 1, FLinearColor::Red, 120, 1);
	}

	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + Forward * 100.f, 1, FLinearColor::White, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + LeftOfSpread * 100.f, 1, FLinearColor::Gray, 120, 1);
	UKismetSystemLibrary::DrawDebugArrow(GetAvatarActorFromActorInfo(), SocketLocation, SocketLocation + RightOfSpread * 100.f, 1, FLinearColor::Gray, 120, 1);


	//FTransform SpawnTransform;
	//SpawnTransform.SetLocation(SocketLocation);

	//SpawnTransform.SetRotation(Rotation.Quaternion());

	//// Prepare projectile actor ready for spawn
	//AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);


	//Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefault();


	//Projectile->FinishSpawning(SpawnTransform);
}
