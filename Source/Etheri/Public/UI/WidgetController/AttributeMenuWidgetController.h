// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/EtheriWidgetController.h"
#include "AttributeMenuWidgetController.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ETHERI_API UAttributeMenuWidgetController : public UEtheriWidgetController
{
	GENERATED_BODY()
public:

	virtual void BroadcastInitialValues() override;

	virtual void BindCallbacksToDependencies() override;
};
