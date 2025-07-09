// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "EtheriGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ETHERI_API UEtheriGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag DefaultInputTag;
};
