// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "EtheriCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class AEtheriHUD;
/**
 * 
 */
UCLASS()
class ETHERI_API AEtheriCharacter : public ACharacterBase
{
	GENERATED_BODY()
	
public:
	AEtheriCharacter();
protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;
private:
	void InitAbilityActorInfo();

	

	UPROPERTY(EditAnywhere, Category = "Display")
	TObjectPtr<UCameraComponent> EtheriCamera;

	UPROPERTY(EditAnywhere, Category = "Display")
	TObjectPtr<USpringArmComponent> EtheriSpringArm;
};
