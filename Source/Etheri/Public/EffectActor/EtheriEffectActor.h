// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EtheriEffectActor.generated.h"

class UGameplayEffect;

UCLASS()
class ETHERI_API AEtheriEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEtheriEffectActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectToActor(AActor* TargetActor, TSubclassOf<UGameplayEffect> GameplayEffectClass);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

private:
	
public:	
	

};
