// Copyright Iron Goblin Corp. 2023


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "Actor/AuraProjectile.h"
#include "Interaction/CombatInterface.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	// Check that we have authority over this ability 
	const bool bIsServer = HasAuthority(&ActivationInfo);

	// Exit if we are not the server
	if (!bIsServer) return;

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());

	if (CombatInterface)
	{
		const FVector SocketLocation = CombatInterface->GetCombatSocketLocation();
		//TODO: Set projectile rotation

		FTransform SpawnTransform;
		SpawnTransform.SetLocation(SocketLocation);

		// Prepare projectile actor ready for spawn
		AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(ProjectileClass, SpawnTransform, GetOwningActorFromActorInfo(), Cast<APawn>(GetOwningActorFromActorInfo()), ESpawnActorCollisionHandlingMethod::AlwaysSpawn);


		//TODO: Give the projectile a Gameplay Effect Spec for causing damage;
		Projectile->FinishSpawning(SpawnTransform);
	}
}
