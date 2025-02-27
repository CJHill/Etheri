// Copyright. Hillz Studios


#include "UI/WidgetController/EtheriWidgetController.h"

void UEtheriWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WidgetControllerParams)
{
	PlayerController = WidgetControllerParams.PlayerController;
	PlayerState = WidgetControllerParams.PlayerState;
	AbilitySystemComponent = WidgetControllerParams.AbilitySystemComponent;
	AttributeSet = WidgetControllerParams.AttributeSet;
}

void UEtheriWidgetController::BroadcastInitialValues()
{

}

void UEtheriWidgetController::BindCallbacksToDependencies()
{
}
