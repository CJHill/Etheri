// Copyright. Hillz Studios


#include "GAS/EtheriAttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "Tag/EtheriGameplayTags.h"


UEtheriAttributeSet::UEtheriAttributeSet()
{
	const FEtheriGameplayTags& gameplayTags = FEtheriGameplayTags::Get();

	TagsToAttributes.Add(gameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);
	
	TagsToAttributes.Add(gameplayTags.Attributes_Secondary_Armour, GetArmourAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Secondary_ArmourPenetration, GetArmourPenetrationAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Secondary_CriticalHitRate, GetCriticalHitRateAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Secondary_HealthRegen, GetHealthRegenAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);
	TagsToAttributes.Add(gameplayTags.Attributes_Secondary_ManaRegen, GetManaRegenAttribute);

}

void UEtheriAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, Vigor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, Resilience, COND_None, REPNOTIFY_Always);

	//Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, Armour, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, ArmourPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, CriticalHitRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, HealthRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, ManaRegen, COND_None, REPNOTIFY_Always);

	//Vital Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	
}

void UEtheriAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
}

void UEtheriAttributeSet::GetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Properties) const
{
	
	Properties.EffectContextHandle = Data.EffectSpec.GetContext();
	Properties.SourceAbilitySystemComponent = Properties.EffectContextHandle.GetInstigatorAbilitySystemComponent();

	/*
	the reason for not using the negation operator (!) and returning early when checking the source ability system component is because the source actor doesn't always have or need an ability system component
	eg. a health potion doesn't need an ability system component
	*/
	if (IsValid(Properties.SourceAbilitySystemComponent) 
		&& Properties.SourceAbilitySystemComponent->AbilityActorInfo.IsValid() 
		&& Properties.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.IsValid())
	{
		Properties.SourceActor = Properties.SourceAbilitySystemComponent->AbilityActorInfo->AvatarActor.Get();
		Properties.SourceController = Properties.SourceAbilitySystemComponent->AbilityActorInfo->PlayerController.Get();

		if (Properties.SourceController && Properties.SourceActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Properties.SourceActor))
			{
				Properties.SourceController = Pawn->GetController();
			}
		}
		if (Properties.SourceController)
		{
			Properties.SourceCharacter = Cast<ACharacter>(Properties.SourceController->GetPawn());
		}
		
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Properties.TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Properties.TargetCharacter = Cast<ACharacter>(Properties.TargetActor);
		Properties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Properties.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Properties.TargetActor);
	}
}

void UEtheriAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Props;
	GetEffectProperties(Data, Props);
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0, GetMaxMana()));
	}
}

void UEtheriAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Strength, OldStrength);
}

void UEtheriAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Vigor, OldVigor);
}

void UEtheriAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Intelligence, OldIntelligence);
}

void UEtheriAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Resilience, OldResilience);
}

void UEtheriAttributeSet::OnRep_Armour(const FGameplayAttributeData& OldArmour) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Armour, OldArmour);
}

void UEtheriAttributeSet::OnRep_ArmourPenetration(const FGameplayAttributeData& OldArmourPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, ArmourPenetration, OldArmourPenetration);
}

void UEtheriAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, BlockChance, OldBlockChance);
}

void UEtheriAttributeSet::OnRep_CriticalHitRate(const FGameplayAttributeData& OldCriticalHitRate) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, CriticalHitRate, OldCriticalHitRate);
}

void UEtheriAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UEtheriAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UEtheriAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Health, OldHealth);
}

void UEtheriAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, MaxHealth, OldMaxHealth);
}

void UEtheriAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, HealthRegen, OldHealthRegen);
}

void UEtheriAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Mana, OldMana);
}

void UEtheriAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, MaxMana, OldMaxMana);
}

void UEtheriAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, ManaRegen, OldManaRegen);
}


