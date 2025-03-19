// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "EtheriAbilitySystemComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FEffectAssetTags, const FGameplayTagContainer&/*Asset Tags*/);
/**
 * 
 */
UCLASS()
class ETHERI_API UEtheriAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:

	void AbilityActorInfoSet();

	FEffectAssetTags EffectAssetTags;
protected:
	void EffectApplied(UAbilitySystemComponent* InASC, const FGameplayEffectSpec& InGESpec, FActiveGameplayEffectHandle InActiveGEHandle);

};
