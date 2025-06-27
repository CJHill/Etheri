// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "EtheriInputConfig.h"
#include "EtheriInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ETHERI_API UEtheriInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	template<class UserClass, typename PressedFunctionType, typename ReleasedFunctionType, typename HeldFunctionType>
	void BindAbilityActions(const UEtheriInputConfig* InputConfig, UserClass* object, PressedFunctionType PressedFunction, ReleasedFunctionType ReleasedFunction, HeldFunctionType HeldFunction);
};

template<class UserClass, typename PressedFunctionType, typename ReleasedFunctionType, typename HeldFunctionType>
inline void UEtheriInputComponent::BindAbilityActions(const UEtheriInputConfig* InputConfig, UserClass* Object, PressedFunctionType PressedFunction, ReleasedFunctionType ReleasedFunction, HeldFunctionType HeldFunction)
{
	check(InputConfig);

	for (const FEtheriInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunction)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunction, Action.InputTag);
			}
			if (ReleasedFunction)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunction, Action.InputTag);
			}
			if (HeldFunction)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunction, Action.InputTag);
			}
		}
	}
}
