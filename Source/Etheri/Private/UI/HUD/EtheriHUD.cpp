// Copyright. Hillz Studios


#include "UI/HUD/EtheriHUD.h"
#include "UI/Widget/EtheriUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

void AEtheriHUD::InitOverlay(APlayerController* PController, APlayerState* PState, UAbilitySystemComponent* ASComponent, UAttributeSet* ASet)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialised!, check HUD classes and BPs"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialised!, check Widget Controller classes and BPs"))

	UUserWidget* widgetOverlay = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);

	OverlayWidget = Cast<UEtheriUserWidget>(widgetOverlay);

	FWidgetControllerParams widgetControllerParams(PController, PState, ASComponent, ASet);
	UOverlayWidgetController* overlayWidgetController = GetOverlayWidgetController(widgetControllerParams);

	OverlayWidget->SetWidgetController(overlayWidgetController);

	overlayWidgetController->BroadcastInitialValues();
	
	widgetOverlay->AddToViewport();
}



UOverlayWidgetController* AEtheriHUD::GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (OverlayWidgetController == nullptr)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WidgetControllerParams);
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
	}
	return OverlayWidgetController;
}

UAttributeMenuWidgetController* AEtheriHUD::GetAttributeMenuWidgetController(const FWidgetControllerParams& WidgetControllerParams)
{
	if (AttributeMenuController == nullptr)
	{
		AttributeMenuController = NewObject<UAttributeMenuWidgetController>(this, AttributeMenuControllerClass);
		AttributeMenuController->SetWidgetControllerParams(WidgetControllerParams);
		AttributeMenuController->BindCallbacksToDependencies();
		return AttributeMenuController;
	}
	return AttributeMenuController;
}
