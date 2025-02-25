// Copyright. Hillz Studios


#include "UI/Widget/EtheriUserWidget.h"

void UEtheriUserWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
