// Copyright. Hillz Studios


#include "Characters/EtheriCharacter.h"

#include "AbilitySystemComponent.h"
#include "GAS/EtheriAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/EtheriPlayerController.h"
#include "Player/EtheriPlayerState.h"
#include "UI/HUD/EtheriHUD.h"

AEtheriCharacter::AEtheriCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;
}

void AEtheriCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AEtheriCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	// Init ability actor info for the Client
	InitAbilityActorInfo();
}

int32 AEtheriCharacter::GetLevel()
{
	const AEtheriPlayerState* EtheriPlayerState = GetPlayerState<AEtheriPlayerState>();
	check(EtheriPlayerState);
	return EtheriPlayerState->GetPlayerLevel();
}

void AEtheriCharacter::InitAbilityActorInfo()
{
	AEtheriPlayerState* EtheriPlayerState = GetPlayerState<AEtheriPlayerState>();
	check(EtheriPlayerState);
	EtheriPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(EtheriPlayerState, this);
	Cast<UEtheriAbilitySystemComponent>(EtheriPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = EtheriPlayerState->GetAbilitySystemComponent();
	AttributeSet = EtheriPlayerState->GetAttributeSet();

	if (AEtheriPlayerController* EtheriPlayerController = Cast<AEtheriPlayerController>(GetController()))
	{
		if (AEtheriHUD* EtheriHUD = Cast<AEtheriHUD>(EtheriPlayerController->GetHUD()))
		{
			EtheriHUD->InitOverlay(EtheriPlayerController, EtheriPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}
