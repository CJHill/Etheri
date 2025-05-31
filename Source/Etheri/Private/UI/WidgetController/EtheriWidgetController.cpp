// Copyright. Hillz Studios



#include "UI/WidgetController/EtheriWidgetController.h"

void UEtheriWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
}

void UEtheriWidgetController::BroadcastInitialValues()
{

}

void UEtheriWidgetController::BindCallbacksToDependencies()
{

}
