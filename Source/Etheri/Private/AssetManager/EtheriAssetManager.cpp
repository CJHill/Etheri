// Copyright. Hillz Studios


#include "AssetManager/EtheriAssetManager.h"
#include "Tag/EtheriGameplayTags.h"
#include "AbilitySystemGlobals.h"

UEtheriAssetManager& UEtheriAssetManager::Get()
{
	check(GEngine);

	UEtheriAssetManager* EtheriAssetManager = Cast<UEtheriAssetManager>(GEngine->AssetManager);

	return *EtheriAssetManager;
}

void UEtheriAssetManager::StartInitialLoading()
{
	Super::StartInitialLoading();

	FEtheriGameplayTags::InitNativeGameplayTags();
	UAbilitySystemGlobals::Get().InitGlobalData(); // This is required to use target data.
}
