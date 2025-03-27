// Copyright. Hillz Studios


#include "Characters/EtheriCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/EtheriPlayerState.h"
#include "AbilitySystemComponent.h"
#include "UI/HUD/EtheriHUD.h"
#include "Player/EtheriPlayerController.h"
#include "GAS/EtheriAbilitySystemComponent.h"


AEtheriCharacter::AEtheriCharacter()
{
	EtheriSpringArm = CreateDefaultSubobject<USpringArmComponent>("Player SpringArm");
	EtheriSpringArm->SetupAttachment(GetMesh());
	EtheriSpringArm->TargetArmLength = 800.f;
	EtheriSpringArm->bUsePawnControlRotation = false;
	EtheriSpringArm->bInheritPitch = false;
	EtheriSpringArm->bInheritRoll = false;
	EtheriSpringArm->bInheritYaw = false;

	EtheriCamera = CreateDefaultSubobject<UCameraComponent>("Player Camera");
	EtheriCamera->SetupAttachment(EtheriSpringArm, USpringArmComponent::SocketName);
	EtheriCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	
	
}

void AEtheriCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//Don't need authority check as possessed by is only called on the server
	InitAbilityActorInfo();
	
}

void AEtheriCharacter::OnRep_PlayerState()
{
	InitAbilityActorInfo();
}

void AEtheriCharacter::InitAbilityActorInfo()
{
	AEtheriPlayerState* etheriPlayerState = GetPlayerState<AEtheriPlayerState>();
	if (etheriPlayerState)
	{
		etheriPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(etheriPlayerState, this);
		Cast<UEtheriAbilitySystemComponent>(etheriPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
		AbilitySystemComponent = etheriPlayerState->GetAbilitySystemComponent();
		AttributeSet = etheriPlayerState->GetAttributeSet();
	}
	if (AEtheriPlayerController* etheriPlayerController = Cast<AEtheriPlayerController>(GetController()))
	{
		if (AEtheriHUD* etheriHUD = Cast<AEtheriHUD>(etheriPlayerController->GetHUD()))
		{
			etheriHUD->InitOverlay(etheriPlayerController, etheriPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
	InitPrimaryAttributes();
}
