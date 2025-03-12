// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "GameplayEffectTypes.h"
#include "EtheriEffectActor.generated.h"

class UGameplayEffect;
class UAbilitySystemComponent;

UENUM(BlueprintType)
enum class EApplyEffectPolicy : uint8
{
	AEP_ApplyOnOverlap UMETA(DisplayName = "Apply On Overlap"),
	AEP_ApplyOnEndOverlap UMETA(DisplayName = "Apply On End Overlap"),
	AEP_DoNotApply UMETA(DisplayName = "Do Not Apply")
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy:uint8
{
	ERP_RemoveOnEndOverlap UMETA(DisplayName = "Remove On End Overlap"),
	ERP_DoNotRemove UMETA(DisplayName = "Do Not Remove")
};

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

	/*friend uint32 GetTypeHash(const FAppliesGameplayEffect& Effect)
	{
		return HashCombine(GetTypeHash(Effect.GEClass),
			HashCombine(GetTypeHash(static_cast<uint8>(Effect.ApplicationEffectPolicy)),
				GetTypeHash(static_cast<uint8>(Effect.RemovalEffectPolicy))));
	}*/
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
	/*friend bool operator==(const FActiveEffectRemovalHandle& A, const FActiveEffectRemovalHandle& B)
	{
		return A.ActiveEffect == B.ActiveEffect &&
			A.ActiveEffectHandle == B.ActiveEffectHandle;
	}

	friend uint32 GetTypeHash(const FActiveEffectRemovalHandle& Handle)
	{
		return HashCombine(GetTypeHash(Handle.ActiveEffect), GetTypeHash(Handle.ActiveEffectHandle));
	}*/
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

	UFUNCTION(BlueprintCallable)
	void ApplyGameplayEffectToActor(AActor* TargetActor, const FAppliesGameplayEffect& GameplayEffect);



	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Gameplay Effects")
	TArray<FAppliesGameplayEffect> GameplayEffectsToApply;
	
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveGameEffectHandles;

	TMultiMap<UAbilitySystemComponent*, FActiveEffectRemovalHandle> ActiveGameEffects;
private:
	
public:	
	

};
