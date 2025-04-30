// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "EtheriAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class ETHERI_API UEtheriAssetManager : public UAssetManager
{
	GENERATED_BODY()
	
public:
	static UEtheriAssetManager& Get();

protected:
	virtual void StartInitialLoading() override;
};
