// Copyright Iron Goblin Corp. 2023


#include "AbilitySystem/Debuff/DebuffNiagaraComponent.h"
#include "AbilitySystemComponent.h"
#include <AbilitySystemBlueprintLibrary.h>
#include <Interaction/CombatInterface.h>

UDebuffNiagaraComponent::UDebuffNiagaraComponent()
{
	bAutoActivate = false;
}

void UDebuffNiagaraComponent::BeginPlay()
{
	Super::BeginPlay();

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetOwner());
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetOwner());
	if (ASC)
	{
		ASC->RegisterGameplayTagEvent(DebuffTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UDebuffNiagaraComponent::DebuffTagChanged);
	}
	// If this was instantiated befure the ASC was added, then we add a delegate that will be broadcast
	// upon the ASC being added, ensuring that either way we register the event
	else if (CombatInterface)
	{
		// Use WeakLambda which doesn't add to the reference count and therefore this component can be
		// garbage collected without needing to dereference this
		CombatInterface->GetOnASCRegisteredDeletgate().AddWeakLambda(this, [this](UAbilitySystemComponent* InASC) 
			{
				InASC->RegisterGameplayTagEvent(DebuffTag, EGameplayTagEventType::NewOrRemoved).AddUObject(this, &UDebuffNiagaraComponent::DebuffTagChanged);
			});
	}
	if (CombatInterface)
	{
		CombatInterface->GetOnDeathDelegate().AddDynamic(this, &UDebuffNiagaraComponent::OnOwnerDeath);
	}

}

void UDebuffNiagaraComponent::DebuffTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	if (NewCount > 0) Activate();
	else Deactivate();
}

void UDebuffNiagaraComponent::OnOwnerDeath(AActor* DeadActor)
{
	Deactivate();
}
