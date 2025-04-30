// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EtheriHUD.generated.h"

class UEtheriUserWidget;
class UOverlayWidgetController;
class UAttributeMenuWidgetController;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
/**
 * 
 */
UCLASS()
class ETHERI_API AEtheriHUD : public AHUD
{
	GENERATED_BODY()
	
public:


	void InitOverlay(APlayerController* PController, APlayerState* PState, UAbilitySystemComponent* ASComponent, UAttributeSet* ASet);

	
protected:
	
private:
	//Overlay Widget Properties
	UPROPERTY()
	TObjectPtr<UEtheriUserWidget> OverlayWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UEtheriUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;

	//Attribute Menu Widget Properties

	UPROPERTY()
	TObjectPtr<UAttributeMenuWidgetController> AttributeMenuController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeMenuWidgetController> AttributeMenuControllerClass;
public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);

	UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const FWidgetControllerParams& WidgetControllerParams);
};
