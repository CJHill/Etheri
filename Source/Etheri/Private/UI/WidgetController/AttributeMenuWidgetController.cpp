// Copyright. Hillz Studios


#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "GAS/EtheriAttributeSet.h"
#include "GAS/Data/AttributeInfoAsset.h"
#include "Tag/EtheriGameplayTags.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UEtheriAttributeSet* attributeSet = Cast<UEtheriAttributeSet>(AttributeSet);
	
	check(AttributeInfo);
	FEtheriAttributeInfo info = AttributeInfo->FindAttributeInfoForTag(FEtheriGameplayTags::Get().Attributes_Primary_Strength);

	info.AttributeValue = attributeSet->GetStrength();

	AttributeInfoDelegate.Broadcast(info);
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
}
