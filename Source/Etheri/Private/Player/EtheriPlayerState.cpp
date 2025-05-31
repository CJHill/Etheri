// Copyright. Hillz Studios



#include "Player/EtheriPlayerState.h"

#include "GAS/EtheriAbilitySystemComponent.h"
#include "GAS/EtheriAttributeSet.h"
#include "Net/UnrealNetwork.h"

AEtheriPlayerState::AEtheriPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UEtheriAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	AttributeSet = CreateDefaultSubobject<UEtheriAttributeSet>("Attribute Set");

	NetUpdateFrequency = 100.f;
}

void AEtheriPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AEtheriPlayerState, Level);
}

UAbilitySystemComponent* AEtheriPlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AEtheriPlayerState::OnRep_Level(int32 OldLevel)
{

}

