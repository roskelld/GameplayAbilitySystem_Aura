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

void AAuraEffectActor::ApplyEffectToTarget(AActor* Target, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	// Built in library call to find an ability system that will be used to
	// do the effect logic
	UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Target);

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
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, EffectContextHandle);

	// EffectSpecHandle wrapper has the Data for the spec as a pointer
	// Using Get pulls in the data, and adding * dereferences it to the 
	// data so it can be given as a const ref.  
	TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}
