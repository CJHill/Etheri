// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EtheriHUD.generated.h"

class UAttributeMenuWidgetController;
class UAttributeSet;
class UAbilitySystemComponent;
class UOverlayWidgetController;
class UEtheriUserWidget;
struct FWidgetControllerParams;
/**
 *
 */
UCLASS()
class ETHERI_API AEtheriHUD : public AHUD
{
	GENERATED_BODY()
public:

	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WCParams);
	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WCParams);

	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

protected:


private:

	UPROPERTY()
	TObjectPtr<UEtheriUserWidget>  OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UEtheriUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuWidgetControllerClass;
};
