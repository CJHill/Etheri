// Copyright. Hillz Studios


#include "GAS/EtheriAbilitySystemComponent.h"
#include "Tag/EtheriGameplayTags.h"
#include "GAS/Abilities/EtheriGameplayAbility.h"

void UEtheriAbilitySystemComponent::AbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UEtheriAbilitySystemComponent::EffectApplied);
	const FEtheriGameplayTags& GameplayTags = FEtheriGameplayTags::Get();
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Orange, FString::Printf(TEXT("Tag: %s"), *GameplayTags.Attributes_Secondary_Armour.ToString()));
}

void UEtheriAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& CharacterAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : CharacterAbilities)
	{
		FGameplayAbilitySpec abilitySpec = FGameplayAbilitySpec(AbilityClass, 1);

		if (const UEtheriGameplayAbility* etheriAbility = Cast<UEtheriGameplayAbility>(abilitySpec.Ability))
		{
			abilitySpec.DynamicAbilityTags.AddTag(etheriAbility->DefaultInputTag);
			GiveAbility(abilitySpec);
		}
		
	}
}

void UEtheriAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (!AbilitySpec.IsActive())
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UEtheriAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void UEtheriAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* InASC, const FGameplayEffectSpec& InGESpec, FActiveGameplayEffectHandle InActiveGEHandle)
{
	FGameplayTagContainer gameplayTagContainer;
	InGESpec.GetAllAssetTags(gameplayTagContainer);

	EffectAssetTags.Broadcast(gameplayTagContainer);

}
