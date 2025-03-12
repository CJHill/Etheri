// Copyright. Hillz Studios


#include "EffectActor/EtheriEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "GAS/EtheriAttributeSet.h"
// Sets default values
AEtheriEffectActor::AEtheriEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Scene Root"));
	
}




void AEtheriEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEtheriEffectActor::ApplyGameplayEffectToActor(AActor* TargetActor, const FAppliesGameplayEffect& GameplayEffect)
{
	UAbilitySystemComponent* targetActorASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (targetActorASC == nullptr) return;

	FGameplayEffectContextHandle gameplayEffectContextHandle = targetActorASC->MakeEffectContext();
	gameplayEffectContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle gameplayEffectSpecHandle = targetActorASC->MakeOutgoingSpec(GameplayEffect.GEClass, 1.0f, gameplayEffectContextHandle);

	FActiveGameplayEffectHandle activeGameplayEffectHandle = targetActorASC->ApplyGameplayEffectSpecToSelf(*gameplayEffectSpecHandle.Data.Get());

	const bool bIsInfinite = gameplayEffectSpecHandle.Data.Get()->Def.Get()->DurationPolicy == EGameplayEffectDurationType::Infinite;

	if (bIsInfinite && GameplayEffect.RemovalEffectPolicy == EEffectRemovalPolicy::ERP_RemoveOnEndOverlap)
	{
		ActiveGameEffects.Add(targetActorASC,{GameplayEffect, activeGameplayEffectHandle});
	}
}



void AEtheriEffectActor::OnOverlap(AActor* TargetActor)
{
	UAbilitySystemComponent* targetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(targetASC)) return;
	for (const auto& Effect : GameplayEffectsToApply)
	{
		if (Effect.ApplicationEffectPolicy == EApplyEffectPolicy::AEP_ApplyOnOverlap)
		{
			ApplyGameplayEffectToActor(TargetActor, Effect);
		}
	}
}

void AEtheriEffectActor::OnEndOverlap(AActor* TargetActor)
{
	UAbilitySystemComponent* targetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (!IsValid(targetASC)) return;
	
	TArray<FActiveEffectRemovalHandle> effectsToRemove;

	for (const auto& Effect : GameplayEffectsToApply)
	{
		if (Effect.ApplicationEffectPolicy == EApplyEffectPolicy::AEP_ApplyOnEndOverlap)
		{
			ApplyGameplayEffectToActor(TargetActor, Effect);
		}
		
	}
	ActiveGameEffects.MultiFind(targetASC, effectsToRemove);
	for (const auto& Effect : effectsToRemove)
	{
		if (Effect.ActiveEffect.RemovalEffectPolicy == EEffectRemovalPolicy::ERP_RemoveOnEndOverlap)
		{
			targetASC->RemoveActiveGameplayEffect(Effect.ActiveEffectHandle, 1);
			ActiveGameEffects.Remove(targetASC, Effect);
		}
	}
	if (bDestroyOnEffectRemoval)
	{
		Destroy();
	}
	
}




