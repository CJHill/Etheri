// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "Characters/CharacterBase.h"
#include "Interface/EnemyInterface.h"
#include "UlgarCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ETHERI_API AUlgarCharacter : public ACharacterBase, public IEnemyInterface
{
	GENERATED_BODY()
public:
	AUlgarCharacter();

	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;

	
};
