// Copyright. Hillz Studios


#include "Player/EtheriPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interface/EnemyInterface.h"

AEtheriPlayerController::AEtheriPlayerController()
{
	bReplicates = true;
}

void AEtheriPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CursorTrace();
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

void AEtheriPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* enhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	enhancedInputComponent->BindAction(EtheriMovement_IA, ETriggerEvent::Triggered, this, &AEtheriPlayerController::Move);
}

void AEtheriPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D inputAxisVector = InputActionValue.Get<FVector2D>();

	const FRotator rotation = GetControlRotation();
	const FRotator yawRotation(0.f, rotation.Yaw, 0.f);
	
	// In Unreal the forward direction is the x axis
	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rightDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* controlledPawn = GetPawn<APawn>())
	{
		//forward direction here represents the W and S keys which are used by the player to move along the Y axis
		controlledPawn->AddMovementInput(forwardDirection, inputAxisVector.Y);
		controlledPawn->AddMovementInput(rightDirection, inputAxisVector.X);
	}
}

void AEtheriPlayerController::CursorTrace()
{
	FHitResult cursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, cursorHit);
	if (!cursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = cursorHit.GetActor();
	if (ThisActor != LastActor)
	{
		if (LastActor != nullptr)
		{
			LastActor->UnHighlightActor();
		}

		if (ThisActor != nullptr)
		{
			ThisActor->HighlightActor();
		}
	}
}
