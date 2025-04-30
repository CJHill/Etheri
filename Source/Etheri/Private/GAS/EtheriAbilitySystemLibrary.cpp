// Copyright. Hillz Studios


#include "GAS/EtheriAbilitySystemLibrary.h"
#include <UI/HUD/EtheriHUD.h>
#include <Player/EtheriPlayerState.h>
#include "UI/WidgetController/EtheriWidgetController.h"


UOverlayWidgetController* UEtheriAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* playerController = WorldContextObject->GetWorld()->UWorld::GetFirstPlayerController())
	{
		if (AEtheriHUD* etheriHUD = Cast<AEtheriHUD>(playerController->GetHUD()))
		{
			AEtheriPlayerState* playerState = playerController->GetPlayerState<AEtheriPlayerState>();
			UAbilitySystemComponent* abilitySystemComponent = playerState->GetAbilitySystemComponent();
			UAttributeSet* attributeSet = playerState->GetAttributeSet();

			const FWidgetControllerParams widgetControllerParams(playerController, playerState, abilitySystemComponent, attributeSet);

			return etheriHUD->GetOverlayWidgetController(widgetControllerParams);
			
		}
	}
	return nullptr;
}

UAttributeMenuWidgetController* UEtheriAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* playerController = WorldContextObject->GetWorld()->UWorld::GetFirstPlayerController())
	{
		if (AEtheriHUD* etheriHUD = Cast<AEtheriHUD>(playerController->GetHUD()))
		{
			AEtheriPlayerState* playerState = playerController->GetPlayerState<AEtheriPlayerState>();
			UAbilitySystemComponent* abilitySystemComponent = playerState->GetAbilitySystemComponent();
			UAttributeSet* attributeSet = playerState->GetAttributeSet();

			const FWidgetControllerParams widgetControllerParams(playerController, playerState, abilitySystemComponent, attributeSet);

			return etheriHUD->GetAttributeMenuWidgetController(widgetControllerParams);

		}
	}
	return nullptr;
}
