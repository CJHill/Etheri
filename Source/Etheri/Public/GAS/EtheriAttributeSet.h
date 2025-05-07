// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "EtheriAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

//The purpose of this struct is to encapsulate the source and target actors properties which are obtained from the Data parameter found in PostGameplayEffectExecute
USTRUCT()
struct FEffectProperties
{
	// Source = causer of the effect, Target = target of the effect 
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	AActor* SourceActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* SourceAbilitySystemComponent =nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;

	UPROPERTY()
	AActor* TargetActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetAbilitySystemComponent = nullptr;
};
//Used for FGameplayAttribute but this template can be used to create aliases for all static function pointers
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;
/*
* 
*/
UCLASS()
class ETHERI_API UEtheriAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UEtheriAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	//Used for clamping current attribute values to the max attribute values
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;

	/*
	* Primary Atrributes
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Atrributes")
	FGameplayAttributeData Strength;
	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Atrributes")
	FGameplayAttributeData Vigor;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, Vigor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Atrributes")
	FGameplayAttributeData Intelligence;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Atrributes")
	FGameplayAttributeData Resilience;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, Resilience);

	/*
	* Secondary Attributes
	*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armour, Category = "Secondary Atrributes")
	FGameplayAttributeData Armour;
	UFUNCTION()
	void OnRep_Armour(const FGameplayAttributeData& OldArmour) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, Armour);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmourPenetration, Category = "Secondary Atrributes")
	FGameplayAttributeData ArmourPenetration;
	UFUNCTION()
	void OnRep_ArmourPenetration(const FGameplayAttributeData& OldArmourPenetration) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, ArmourPenetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Secondary Atrributes")
	FGameplayAttributeData BlockChance;
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, BlockChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitRate, Category = "Secondary Atrributes")
	FGameplayAttributeData CriticalHitRate;
	UFUNCTION()
	void OnRep_CriticalHitRate(const FGameplayAttributeData& OldCriticalHitRate) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, CriticalHitRate);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Atrributes")
	FGameplayAttributeData CriticalHitDamage;
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Atrributes")
	FGameplayAttributeData CriticalHitResistance;
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, CriticalHitResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Atrributes")
	FGameplayAttributeData MaxHealth;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, MaxHealth)
	

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegen, Category = "Secondary Atrributes")
	FGameplayAttributeData HealthRegen;
	UFUNCTION()
	void OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, HealthRegen)


	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Atrributes")
	FGameplayAttributeData MaxMana;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, MaxMana)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegen, Category = "Secondary Atrributes")
	FGameplayAttributeData ManaRegen;
	UFUNCTION()
	void OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen) const;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, ManaRegen)

	/*
	* Vital Attributes start at begin health comment
	*/

	//Begin Health attribute properties---------------------------------------
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Atrributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, Health)
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
	//End Health attribute properties-------------------------------------------

	//Begin Mana attribute properties---------------------------------------
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Atrributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UEtheriAttributeSet, Mana)
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	//End Mana attribute properties-------------------------------------------

private:
	// Uses the Data variable passed in from PostGameplayEffectExecute to assign to the apropriate value in the FEffectProperties struct
	void GetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Properties) const;

};
