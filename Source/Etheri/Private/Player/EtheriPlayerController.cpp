// Copyright. Hillz Studios


#include "Player/EtheriPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Input/EtheriInputComponent.h"
#include "Interface/EnemyInterface.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GAS/EtheriAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Tag/EtheriGameplayTags.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"

AEtheriPlayerController::AEtheriPlayerController()
{
	bReplicates = true;
	Spline = CreateDefaultSubobject<USplineComponent>("Spline");
}

void AEtheriPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CursorTrace();
	AutoRun();
}
void AEtheriPlayerController::AutoRun()
{
	if (!bAutoRunning) return;
	if (APawn* controlledPawn = GetPawn())
	{
		const FVector locationOnSpline = Spline->FindLocationClosestToWorldLocation(controlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector directionOnSpline = Spline->FindDirectionClosestToWorldLocation(locationOnSpline, ESplineCoordinateSpace::World);
		controlledPawn->AddMovementInput(directionOnSpline);

		const float distanceToDestination = (locationOnSpline - CachedDestination).Length();
		if (distanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}


void AEtheriPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(Etheri_IMC);

	UEnhancedInputLocalPlayerSubsystem* inputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(!inputSubsystem) return;
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

	UEtheriInputComponent* etheriInputComponent = CastChecked<UEtheriInputComponent>(InputComponent);

	etheriInputComponent->BindAction(EtheriMovement_IA, ETriggerEvent::Triggered, this, &AEtheriPlayerController::Move);

	etheriInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
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
	
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastActor = ThisActor;
	ThisActor = CursorHit.GetActor();
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

void AEtheriPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FEtheriGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}

}

void AEtheriPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{

	if (!InputTag.MatchesTagExact(FEtheriGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagReleased(InputTag);
		}
	}
	else
	{
		const APawn* controlledPawn = GetPawn();
		if (FollowTime <= ShortPressThreshold)
		{
			if (UNavigationPath* navPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, controlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();
				for (const FVector& PointLocation : navPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLocation, ESplineCoordinateSpace::World);
				}
				if (navPath->PathPoints.Num() > 0)
				{
					CachedDestination = navPath->PathPoints[navPath->PathPoints.Num() - 1];
					bAutoRunning = true;
				}
				
			}
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AEtheriPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	
	if (!InputTag.MatchesTagExact(FEtheriGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
		return;
	}
	if (bTargeting)
	{
		if (GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		if (CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;

		}
		if (APawn* controlledPawn = GetPawn())
		{
			const FVector worldDirection = (CachedDestination - controlledPawn->GetActorLocation()).GetSafeNormal();
			controlledPawn->AddMovementInput(worldDirection);
		}
	}
}

UEtheriAbilitySystemComponent* AEtheriPlayerController::GetASC()
{
	if (AbilitySystemComponent == nullptr)
	{
		AbilitySystemComponent = Cast<UEtheriAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AbilitySystemComponent;
}

