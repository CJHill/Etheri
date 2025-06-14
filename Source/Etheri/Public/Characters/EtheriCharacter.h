// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "EtheriCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 *
 */
UCLASS()
class ETHERI_API AEtheriCharacter : public ACharacterBase
{
	GENERATED_BODY()
public:
	AEtheriCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/** Combat Interface */
	virtual int32 GetLevel() override;
	/** end Combat Interface */

private:
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, Category = "Display")
	TObjectPtr<UCameraComponent> EtheriCamera;

	UPROPERTY(EditAnywhere, Category = "Display")
	TObjectPtr<USpringArmComponent> EtheriSpringArm;
};