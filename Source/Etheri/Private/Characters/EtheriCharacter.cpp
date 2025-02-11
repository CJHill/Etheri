// Copyright. Hillz Studios


#include "Characters/EtheriCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


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
