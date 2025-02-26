// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "EtheriHUD.generated.h"

class UEtheriUserWidget;
class UOverlayWidgetController;
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

	UPROPERTY()
	TObjectPtr<UEtheriUserWidget> OverlayWidget;

	void InitOverlay(APlayerController* PController, APlayerState* PState, UAbilitySystemComponent* ASComponent, UAttributeSet* ASet);
protected:
	
private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UEtheriUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
public:
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& WidgetControllerParams);
};
