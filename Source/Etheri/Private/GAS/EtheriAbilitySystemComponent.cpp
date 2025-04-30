// Copyright. Hillz Studios


#include "GAS/EtheriAbilitySystemComponent.h"
#include "Tag/EtheriGameplayTags.h"

void UEtheriAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UEtheriAbilitySystemComponent::EffectApplied);
	const FEtheriGameplayTags& GameplayTags = FEtheriGameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armour.ToString()));
}

void UEtheriAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* InASC, const FGameplayEffectSpec& InGESpec, FActiveGameplayEffectHandle InActiveGEHandle)
{
	FGameplayTagContainer gameplayTagContainer;
	InGESpec.GetAllAssetTags(gameplayTagContainer);

	EffectAssetTags.Broadcast(gameplayTagContainer);

}
