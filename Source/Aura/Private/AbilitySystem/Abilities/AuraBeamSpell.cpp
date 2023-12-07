// Copyright Iron Goblin Corp. 2023


#include "AbilitySystem/Abilities/AuraBeamSpell.h"
#include "GameFramework/Character.h"
#include <Kismet/KismetSystemLibrary.h>
#include <Interaction/CombatInterface.h>
#include <AbilitySystem/AuraAbilitySystemLibrary.h>

void UAuraBeamSpell::StoreMouseDataInfo(const FHitResult& HitResult)
{
	if (HitResult.bBlockingHit)
	{
		MouseHitLocation = HitResult.ImpactPoint;
		MouseHitActor= HitResult.GetActor();
	} 
	else
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
	}
}

void UAuraBeamSpell::StoreOwnerVariables()
{
	if (CurrentActorInfo)
	{
		OwnerCharacter = Cast<ACharacter>(CurrentActorInfo->AvatarActor);
		OwnerPlayerController = CurrentActorInfo->PlayerController.Get();
	}
	
}

void UAuraBeamSpell::TraceFirstTarget(const FVector& BeamTargetLocation)
{
	check(OwnerCharacter);
	if (!OwnerCharacter->Implements<UCombatInterface>()) return;

	;
	if (USkeletalMeshComponent* Weapon = ICombatInterface::Execute_GetWeapon(OwnerCharacter))
	{
		TArray<AActor*> ActorsToIgnore;
		ActorsToIgnore.Add(OwnerCharacter);
		FHitResult HitResult;

		const FVector SocketLocation = Weapon->GetSocketLocation(FName("TipSocket"));
		UKismetSystemLibrary::SphereTraceSingle(OwnerCharacter, SocketLocation, BeamTargetLocation, 10.f, TraceTypeQuery1, false, ActorsToIgnore, EDrawDebugTrace::None, HitResult, true);

		if (HitResult.bBlockingHit)
		{
			MouseHitLocation = HitResult.ImpactPoint;
			MouseHitActor = HitResult.GetActor();
		}
	}
	
}

void UAuraBeamSpell::StoreAdditionalTargets(TArray<AActor*>& OutAdditionalTargets)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	ActorsToIgnore.Add(MouseHitActor);

	TArray<AActor*> OverlappingActors;
	
	UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(GetAvatarActorFromActorInfo(), OverlappingActors, ActorsToIgnore, 850.f, MouseHitActor->GetActorLocation());

	int32 NumAdditionalTargets = FMath::Min(GetAbilityLevel() - 1, MaxNumShockTargets);
	NumAdditionalTargets = 5;

	UAuraAbilitySystemLibrary::GetClosestTargets(NumAdditionalTargets, OverlappingActors, OutAdditionalTargets, MouseHitActor->GetActorLocation());
}
