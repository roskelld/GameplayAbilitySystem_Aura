// Copyright Iron Goblin Corp. 2023

#include "Actor/AuraEffectActor.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot"));
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
}

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// Built in library call to find an ability system that will be used to
	// do the effect logic
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	// Silently exit if the target has no Ability System Component
	// Perhaps a generic actor triggered it
	if (TargetASC == nullptr) return;

	// Crash if called without any provided/valid effect class
	check(GameplayEffectClass);

	// Wrapper object that provides data about the applied effect context
	// Can be used by the effect to probe for data
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();

	// Add the applying object as the source to the spec
	// So that we can know who was the source of this effect
	EffectContextHandle.AddSourceObject(this);

	// Make a Spec Handle of the GamplayEffect from the Context and effect class
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, ActorLevel, EffectContextHandle);

	// EffectSpecHandle wrapper has the Data for the spec as a pointer
	// wrapper Using Get pulls in the data, and adding * dereferences 
	// it to the data so it can be given as a const ref.  
	const FActiveGameplayEffectHandle ActiveEffectHandle = TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	// Is effect being applied of Infinite duration (set in the spec)
	// If so it might need to be tracked so it can later be removed.
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	if (bIsInfinite && InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		// Write to the Effect Actor's handle map the handle 
		// and a pointer to the target ASC so it can be later
		// checked.
		ActiveEffectHandles.Add(ActiveEffectHandle, TargetASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InstantGameplayEffectClass);
	}

	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, DurationGameplayEffectClass);
	}

	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor, InfiniteGameplayEffectClass);
	}

	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;

		// Build an array of handles that need to be remove
		// You can't remove them whilst looping through 
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;

		for (auto HandlePair : ActiveEffectHandles)
		{
			// Does the target actor's ASC match one in the 
			// stored map of ASCs
			if (TargetASC == HandlePair.Value)
			{
				// Hard coded to remove only one stack, this behaviour
				// might not be desired and could need extra info from
				// the designer or maybe checking the GE spec.
				TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
				HandlesToRemove.Add(HandlePair.Key);
			}
		}

		// Loop through all handles and remove them from 
		// stored map
		for (auto& Handle : HandlesToRemove)
		{
			ActiveEffectHandles.FindAndRemoveChecked(Handle);
		}
	}
}
