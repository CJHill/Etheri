// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "GAS/Abilities/EtheriGameplayAbility.h"
#include "EtheriProjectileSpell.generated.h"


/**
 * 
 */
UCLASS()
class ETHERI_API UEtheriProjectileSpell : public UEtheriGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
