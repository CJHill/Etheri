// Copyright. Hillz Studios


#include "GAS/EtheriAbilitySystemComponent.h"

void UEtheriAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UEtheriAbilitySystemComponent::EffectApplied);
}

void UEtheriAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* InASC, const FGameplayEffectSpec& InGESpec, FActiveGameplayEffectHandle InActiveGEHandle)
{
	FGameplayTagContainer gameplayTagContainer;
	InGESpec.GetAllAssetTags(gameplayTagContainer);

	EffectAssetTags.Broadcast(gameplayTagContainer);

}
