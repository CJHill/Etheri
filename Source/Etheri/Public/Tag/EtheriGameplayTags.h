// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 * Etheri Gameplay Tags, 
   This is a singleton containg native Gameplay Tags
 */
struct FEtheriGameplayTags
{
public:
	static const FEtheriGameplayTags& Get() { return GameplayTags; }
	static void InitNativeGameplayTags();

	//Primary Attributes
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Vigor;
	FGameplayTag Attributes_Primary_Resilience;

	//Secondary Attributes
	FGameplayTag Attributes_Secondary_Armour;
	FGameplayTag Attributes_Secondary_ArmourPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CriticalHitRate;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_HealthRegen;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_ManaRegen;

	//Vitals Attributes
	FGameplayTag Attributes_Vitals_Health;
	FGameplayTag Attributes_Vitals_Mana;

	//Input Tags
	FGameplayTag InputTag_TMB1;
	FGameplayTag InputTag_TMB2;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_LMB;

protected:
	
private:
	static FEtheriGameplayTags GameplayTags;
};