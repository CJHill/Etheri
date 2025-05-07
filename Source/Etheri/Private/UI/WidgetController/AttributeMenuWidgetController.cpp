// Copyright. Hillz Studios


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "GAS/EtheriAttributeSet.h"
#include "GAS/Data/AttributeInfoAsset.h"
#include "Tag/EtheriGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UEtheriAttributeSet* AS = Cast<UEtheriAttributeSet>(AttributeSet);
	
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		FEtheriAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS);
		AttributeInfoDelegate.Broadcast(Info);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}
