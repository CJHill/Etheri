// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "EtheriEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

//Different game objects might be applied differently so having on and on end overlap will provide versatility. 
UENUM(BlueprintType)
enum class EApplyEffectPolicy : uint8
{
	AEP_ApplyOnOverlap UMETA(DisplayName = "Apply On Overlap"),
	AEP_ApplyOnEndOverlap UMETA(DisplayName = "Apply On End Overlap"),
	AEP_DoNotApply UMETA(DisplayName = "Do Not Apply")
};

//Mainly needed for infinite gameplay effects as they must be removed manually.
UENUM(BlueprintType)
enum class EEffectRemovalPolicy:uint8
{
	ERP_RemoveOnEndOverlap UMETA(DisplayName = "Remove On End Overlap"),
	ERP_DoNotRemove UMETA(DisplayName = "Do Not Remove")
};

//Encapsulates gameplay effects and their policy properties to make the assignment of gameplay effects much more convenient in the editor
USTRUCT(BlueprintType)
struct FAppliesGameplayEffect
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	TSubclassOf<UGameplayEffect> GEClass = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	EApplyEffectPolicy ApplicationEffectPolicy = EApplyEffectPolicy::AEP_DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	EEffectRemovalPolicy RemovalEffectPolicy = EEffectRemovalPolicy::ERP_DoNotRemove;

	bool operator ==(const FAppliesGameplayEffect& Other) const
	{
		return GEClass == Other.GEClass && ApplicationEffectPolicy == Other.ApplicationEffectPolicy && RemovalEffectPolicy == Other.RemovalEffectPolicy;
	}


};

struct FActiveEffectRemovalHandle
{
	FActiveEffectRemovalHandle(const FAppliesGameplayEffect& InEffect, FActiveGameplayEffectHandle InHandle) : ActiveEffect(InEffect), ActiveEffectHandle(InHandle)
	{

	}
	const FAppliesGameplayEffect& ActiveEffect;
	FActiveGameplayEffectHandle ActiveEffectHandle;

	bool operator==(const FActiveEffectRemovalHandle& Other) const
	{
		return ActiveEffectHandle == Other.ActiveEffectHandle && ActiveEffect == Other.ActiveEffect;
	}

};

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	bool bDestroyOnEffectRemoval = false;

	void ApplyGameplayEffectToActor(AActor* TargetActor, const FAppliesGameplayEffect& GameplayEffect);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	//Allows a game object to apply multiple gameplay effects to a target
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	TArray<FAppliesGameplayEffect> GameplayEffectsToApply;
	
	//Multi Map is used because a target can recieve multiple infinite effects
	TMultiMap<UAbilitySystemComponent*, FActiveEffectRemovalHandle> ActiveGameEffects;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	float ActorLevel = 1.f;
private:
	
public:	
	

};
