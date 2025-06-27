// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameplayTagContainer.h"
#include "EtheriPlayerController.generated.h"

class UInputMappingContext; //Declaration so that this class can be wrapped in a TObjectPtr. Variables of this type will be marked as such VariableName_IMC
class UInputAction; //Declaration so that this class can be wrapped in a TObjectPtr. Variables of this type will be marked as such VariableName_IA
struct FInputActionValue;
class IEnemyInterface;
class UEtheriInputConfig;

UCLASS()
class ETHERI_API AEtheriPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AEtheriPlayerController();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
private:
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> Etheri_IMC;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> EtheriMovement_IA;

	void Move(const FInputActionValue& InputActionValue);

	/**Cursor Trace:
	 * Line trace from cursor. There are several conditions:
	 *  A. LastActor is null && ThisActor is null
	 *		- Do nothing
	 *	B. LastActor is null && ThisActor is valid
	 *		- Highlight ThisActor
	 *	C. LastActor is valid && ThisActor is null
	 *		- UnHighlight LastActor
	 *	D. Both actors are valid, but LastActor != ThisActor
	 *		- UnHighlight LastActor, and Highlight ThisActor
	 *	E. Both actors are valid, and are the same actor
	 *		- Do nothing
	 * Since case A and E both result in nothing happening. We don't need to check for these scenarios. If bugs do occur with this feature these cases will prove useful for debugging
	 */
	void CursorTrace();

	TScriptInterface<IEnemyInterface> LastActor;
	TScriptInterface<IEnemyInterface> ThisActor;

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UEtheriInputConfig> InputConfig;
};
