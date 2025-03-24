// Copyright. Hillz Studios


#include "UI/WidgetController/OverlayWidgetController.h"
#include "GAS/EtheriAttributeSet.h"
#include"GAS/EtheriAbilitySystemComponent.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	const UEtheriAttributeSet* etheriAttributeSet = CastChecked<UEtheriAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(etheriAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(etheriAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(etheriAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(etheriAttributeSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UEtheriAttributeSet* etheriAttributeSet = CastChecked<UEtheriAttributeSet>(AttributeSet);

	/*------------------------------------Health Callback------------------------------*/
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(etheriAttributeSet->GetHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnHealthChanged.Broadcast(Data.NewValue);
		}
	);

	/*------------------------------------MaxHealth Callback------------------------------*/
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(etheriAttributeSet->GetMaxHealthAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChanged.Broadcast(Data.NewValue);
		}
	);
	
	/*------------------------------------Mana Callback------------------------------*/
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(etheriAttributeSet->GetManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnManaChanged.Broadcast(Data.NewValue);
		}
	);

	/*------------------------------------MaxMana Callback------------------------------*/
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(etheriAttributeSet->GetMaxManaAttribute()).AddLambda(
		[this](const FOnAttributeChangeData& Data)
		{
			OnMaxManaChanged.Broadcast(Data.NewValue);
		}
	);

	/*------------------------------------Message Row Callback------------------------------*/
	Cast<UEtheriAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)
		{
			for (const FGameplayTag& Tag : AssetTags)
			{
				//"Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}

			}
		}
	);
}

