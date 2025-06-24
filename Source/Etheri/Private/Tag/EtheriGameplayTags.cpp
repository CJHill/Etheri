// Copyright. Hillz Studios


#include "Tag/EtheriGameplayTags.h"
#include "GameplayTagsManager.h"

FEtheriGameplayTags FEtheriGameplayTags::GameplayTags;

void FEtheriGameplayTags::InitNativeGameplayTags()
{
	//Primary Attributes
	GameplayTags.Attributes_Primary_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strength"), FString("improves physical damage"));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("increases health"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("improves magical damage"));
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("improves armour and resistance to critical hits"));

	//Secondary Attributes
	GameplayTags.Attributes_Secondary_Armour = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armour"), FString("Reduces damage taken, improves Block Chance"));
	GameplayTags.Attributes_Secondary_ArmourPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmourPenetration"), FString("The amount of damage that ignores armour"));
	GameplayTags.Attributes_Secondary_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.BlockChance"), FString("The chance for incoming damage to be cancelled out"));
	GameplayTags.Attributes_Secondary_CriticalHitRate = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitRate"), FString("The chance of a player landing a critical hit"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("The amount of bonus dmg caused by landing a critical hit"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("Reduces the chance of being hit by critical hits"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("Maximum amount of health a player can have"));
	GameplayTags.Attributes_Secondary_HealthRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.HealthRegen"), FString("Passive rate at which health is restored"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("Maximum amount of mana a player can have"));
	GameplayTags.Attributes_Secondary_ManaRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ManaRegen"), FString("Passive rate at which mana is restored"));

	//Vital Attributes
	GameplayTags.Attributes_Vitals_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vitals.Health"), FString("Amount of hit points a player has before they die"));
	GameplayTags.Attributes_Vitals_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vitals.Mana"), FString("Resource used for casting spells"));

	//Input Tags
	GameplayTags.InputTag_TMB1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.TMB1"),
		FString("Input Tag for Thumb Mouse Button 1")
	);

	GameplayTags.InputTag_TMB2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.TMB2"),
		FString("Input Tag for Thumb Mouse Button 2")
	);

	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.1"),
		FString("Input Tag for 1 key")
	);


	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.2"),
		FString("Input Tag for 2 key")
	);

	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.3"),
		FString("Input Tag for 3 key")
	);

	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("InputTag.4"),
		FString("Input Tag for 4 key")
	);


}
