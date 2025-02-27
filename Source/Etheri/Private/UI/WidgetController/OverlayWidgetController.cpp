// Copyright. Hillz Studios


#include "UI/WidgetController/OverlayWidgetController.h"
#include "GAS/EtheriAttributeSet.h"

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
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(etheriAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(etheriAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(etheriAttributeSet->GetManaAttribute()).AddUObject(this, &UOverlayWidgetController::ManaChanged);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(etheriAttributeSet->GetMaxManaAttribute()).AddUObject(this, &UOverlayWidgetController::MaxManaChanged);
}

void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UOverlayWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}
