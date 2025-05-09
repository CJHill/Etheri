// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/EtheriWidgetController.h"
#include <GameplayModMagnitudeCalculation.h>
#include "AttributeMenuWidgetController.generated.h"


struct FGameplayAttribute;
struct FEtheriAttributeInfo;
class UAttributeInfoAsset;


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FEtheriAttributeInfo&, Info);
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

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected: 

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfoAsset> AttributeInfo;

private:
	void BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const;
};
