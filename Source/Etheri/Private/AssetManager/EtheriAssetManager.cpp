// Copyright. Hillz Studios


#include "AssetManager/EtheriAssetManager.h"
#include "Tag/EtheriGameplayTags.h"

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
}
