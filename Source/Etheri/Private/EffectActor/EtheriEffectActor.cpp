// Copyright. Hillz Studios


#include "EffectActor/EtheriEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemInterface.h"
#include "GAS/EtheriAttributeSet.h"
// Sets default values
AEtheriEffectActor::AEtheriEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("Scene Root"));
	
}




void AEtheriEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEtheriEffectActor::ApplyGameplayEffectToActor(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass)
{
	UAbilitySystemComponent* targetActorASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);

	if (targetActorASC == nullptr) return;

	check(GameplayEffectClass);

	FGameplayEffectContextHandle gameplayEffectContextHandle = targetActorASC->MakeEffectContext();
	gameplayEffectContextHandle.AddSourceObject(this);

	FGameplayEffectSpecHandle gameplayEffectSpecHandle = targetActorASC->MakeOutgoingSpec(GameplayEffectClass, 1.0f, gameplayEffectContextHandle);

	targetActorASC->ApplyGameplayEffectSpecToSelf(*gameplayEffectSpecHandle.Data.Get());
}




