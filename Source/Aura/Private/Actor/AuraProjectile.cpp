// Copyright Iron Goblin Corp. 2023

#include "Actor/AuraProjectile.h"
#include "Aura/Aura.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"
#include <AbilitySystemBlueprintLibrary.h>
#include "AbilitySystemComponent.h"
#include "NiagaraFunctionLibrary.h"
#include <AbilitySystem/AuraAbilitySystemLibrary.h>
#include <Net/UnrealNetwork.h>

AAuraProjectile::AAuraProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	Sphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	SetRootComponent(Sphere);
	Sphere->SetCollisionObjectType(ECC_Projectile);
	Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	Sphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	Sphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->InitialSpeed = 550.f;
	ProjectileMovement->MaxSpeed = 550.f;
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AAuraProjectile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AAuraProjectile, HomingTargetSceneComponent);
	DOREPLIFETIME(AAuraProjectile, bHomingProjectile);
	DOREPLIFETIME(AAuraProjectile, HomingAccelerationMagnitude);
	DOREPLIFETIME(AAuraProjectile, HomingTargetLocation);
}

void AAuraProjectile::BeginPlay()
{
	Super::BeginPlay();
	SetLifeSpan(LifeSpan);

	if (bHomingProjectile)
	{
		ProjectileMovement->HomingAccelerationMagnitude = HomingAccelerationMagnitude;
		ProjectileMovement->bIsHomingProjectile = bHomingProjectile;

		if (HomingTargetSceneComponent.IsNull())
		{
			HomingTargetSceneComponent = NewObject<USceneComponent>(USceneComponent::StaticClass());
			HomingTargetSceneComponent->SetWorldLocation(HomingTargetLocation);
			ProjectileMovement->HomingTargetComponent = HomingTargetSceneComponent;
		}
		ProjectileMovement->HomingTargetComponent = HomingTargetSceneComponent;
	}
	else
	{
		SetReplicateMovement(true);
	}

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AAuraProjectile::OnSphereOverlap);
	ProjectileSoundComponent = UGameplayStatics::SpawnSoundAttached(ProjectileSound, GetRootComponent());
}

void AAuraProjectile::Destroyed()
{
	if (!bHit && !HasAuthority()) OnHit();
	if (IsValid(ProjectileSoundComponent))
	{
		ProjectileSoundComponent->Stop();
		ProjectileSoundComponent->DestroyComponent();
	}
	Super::Destroyed();
}

void AAuraProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (DamageEffectParams.SourceAbilitySystemComponent == nullptr) return;

	AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();

	// If source of attack is overlaped actor then return else we damage ourselves
	if (SourceAvatarActor == OtherActor) return;
	if (!UAuraAbilitySystemLibrary::IsNotFriend(SourceAvatarActor, OtherActor)) return; // Prevent damaging friends
	if (!bHit) OnHit();

	if (HasAuthority())
	{
		// Get the ASC of the actor we hit
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
		{
			const FVector DeathImpulse = GetActorForwardVector() * DamageEffectParams.DeathImpulseMagnitude;
			DamageEffectParams.DeathImpulse = DeathImpulse;						// Generate the physics impulse hit on the target

			const bool bKnockback = FMath::RandRange(1, 100) < DamageEffectParams.KnockbackChance;
			if (bKnockback)
			{
				// Generate a rotation based on the actor and the incoming force
				FRotator Rotation = GetActorRotation();
				Rotation.Pitch = 45.f;
				const FVector KnockbackDirection = Rotation.Vector();
				const FVector KnockbackForce = KnockbackDirection * DamageEffectParams.KnockbackForceMagnitude;
				DamageEffectParams.KnockbackForce = KnockbackForce;				// Generate knockback hit on target character
			}

			DamageEffectParams.TargetAbilitySystemComponent = TargetASC;		// Now we've hit a target we know its ASC
			UAuraAbilitySystemLibrary::ApplyDamageEffect(DamageEffectParams);
		}
		
		Destroy();
	}
	else bHit = true;
}

void AAuraProjectile::OnHit()
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), FRotator::ZeroRotator);
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
	if (IsValid(ProjectileSoundComponent))
	{
		ProjectileSoundComponent->Stop();
		ProjectileSoundComponent->DestroyComponent();
	}
	bHit = true;
}

