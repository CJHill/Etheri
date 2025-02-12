// Copyright. Hillz Studios


#include "Player/EtheriPlayerState.h"
#include "GAS/EtheriAbilitySystemComponent.h"
#include "GAS/EtheriAttributeSet.h"

AEtheriPlayerState::AEtheriPlayerState()
{
	MinNetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UEtheriAbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UEtheriAttributeSet>("Attribute Set");
}

UAbilitySystemComponent* AEtheriPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AEtheriPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}
