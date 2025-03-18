// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "EtheriAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class ETHERI_API UEtheriAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:

	void AbilityActorInfoSet();

protected:
	void EffectApplied(UAbilitySystemComponent* InASC, const FGameplayEffectSpec& InGESpec, FActiveGameplayEffectHandle InActiveGEHandle);

};
