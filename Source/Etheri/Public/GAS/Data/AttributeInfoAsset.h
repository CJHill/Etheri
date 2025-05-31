// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "AttributeInfoAsset.generated.h"

USTRUCT(BlueprintType)
struct FEtheriAttributeInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag AttributeTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeName = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText AttributeDescription = FText();

	UPROPERTY(BlueprintReadOnly)
	float AttributeValue = 0.f;
};

/**
 *
 */
UCLASS()
class ETHERI_API UAttributeInfoAsset : public UDataAsset
{
	GENERATED_BODY()
public:
	FEtheriAttributeInfo FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound = false) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FEtheriAttributeInfo> AttributeInformation;
};
