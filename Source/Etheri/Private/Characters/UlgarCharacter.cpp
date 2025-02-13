// Copyright. Hillz Studios


#include "Characters/UlgarCharacter.h"
#include "Etheri/Etheri.h"
#include "GAS/EtheriAbilitySystemComponent.h"
#include "GAS/EtheriAttributeSet.h"

AUlgarCharacter::AUlgarCharacter()
{
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	AbilitySystemComponent = CreateDefaultSubobject<UEtheriAbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UEtheriAttributeSet>("Attribute Set");
}

void AUlgarCharacter::BeginPlay()
{
	Super::BeginPlay();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}


void AUlgarCharacter::HighlightActor()
{

	
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->MarkRenderStateDirty();

	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	WeaponMesh->MarkRenderStateDirty();
}

void AUlgarCharacter::UnHighlightActor()
{

	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}


