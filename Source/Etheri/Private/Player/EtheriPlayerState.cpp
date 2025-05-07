// Copyright. Hillz Studios


#include "Player/EtheriPlayerState.h"
#include "GAS/EtheriAbilitySystemComponent.h"
#include "GAS/EtheriAttributeSet.h"
#include "Net/UnrealNetwork.h"

AEtheriPlayerState::AEtheriPlayerState()
{
	MinNetUpdateFrequency = 100.f;

	AbilitySystemComponent = CreateDefaultSubobject<UEtheriAbilitySystemComponent>("Ability System Component");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	AttributeSet = CreateDefaultSubobject<UEtheriAttributeSet>("Attribute Set");

}

void AEtheriPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AEtheriPlayerState, Level);
}

void AEtheriPlayerState::OnRep_Level(int32 OldLevel)
{
}

UAbilitySystemComponent* AEtheriPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

UAttributeSet* AEtheriPlayerState::GetAttributeSet() const
{
	return AttributeSet;
}

