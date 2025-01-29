// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "EtheriPlayerController.generated.h"

class UInputMappingContext; //Declaration so that this class can be wrapped in a TObjectPtr. Variables of this type will be marked as such VariableName_IMC

UCLASS()
class ETHERI_API AEtheriPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AEtheriPlayerController();

protected:
	virtual void BeginPlay() override;

private:
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> Etheri_IMC;

};
