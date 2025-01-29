// Copyright. Hillz Studios


#include "Player/EtheriPlayerController.h"
#include "EnhancedInputSubsystems.h"

AEtheriPlayerController::AEtheriPlayerController()
{
	bReplicates = true;
}

void AEtheriPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(Etheri_IMC);

	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(inputSubsystem);
	inputSubsystem->AddMappingContext(Etheri_IMC, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI inputModeData;
	inputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	inputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(inputModeData);
}
