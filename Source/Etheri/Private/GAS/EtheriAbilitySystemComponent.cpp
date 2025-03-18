// Copyright. Hillz Studios


#include "GAS/EtheriAbilitySystemComponent.h"

void UEtheriAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UEtheriAbilitySystemComponent::EffectApplied);
}

void UEtheriAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* InASC, const FGameplayEffectSpec& InGESpec, FActiveGameplayEffectHandle InActiveGEHandle)
{
	GEngine->AddOnScreenDebugMessage(1, 10.f, FColor::Blue, FString("Effect applied!"));
}
