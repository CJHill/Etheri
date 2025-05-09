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
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	UEtheriAttributeSet* AS = CastChecked<UEtheriAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			}
		);
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FEtheriAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
