// Copyright. Hillz Studios


#include "GAS/EtheriAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameFramework/Character.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "Tag/EtheriGameplayTags.h"

UEtheriAttributeSet::UEtheriAttributeSet()
{
	const FEtheriGameplayTags& GameplayTags = FEtheriGameplayTags::Get();

	/* Primary Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);

	/* Secondary Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Armour, GetArmourAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ArmourPenetration, GetArmourPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitRate, GetCriticalHitRateAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_HealthRegen, GetHealthRegenAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ManaRegen, GetManaRegenAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);

}

void UEtheriAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Primary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	// Secondary Attributes

	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, Armour, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, ArmourPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, CriticalHitRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, HealthRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, ManaRegen, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UEtheriAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);

	// Vital Attributes

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

void UEtheriAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	// Source = causer of the effect, Target = target of the effect (owner of this AS)

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UEtheriAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

void UEtheriAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Health, OldHealth);
}

void UEtheriAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Mana, OldMana);
}

void UEtheriAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Strength, OldStrength);
}

void UEtheriAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Intelligence, OldIntelligence);
}

void UEtheriAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Resilience, OldResilience);
}

void UEtheriAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, Vigor, OldVigor);
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

void UEtheriAttributeSet::OnRep_HealthRegen(const FGameplayAttributeData& OldHealthRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, HealthRegen, OldHealthRegen);
}

void UEtheriAttributeSet::OnRep_ManaRegen(const FGameplayAttributeData& OldManaRegen) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, ManaRegen, OldManaRegen);
}

void UEtheriAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, MaxHealth, OldMaxHealth);
}

void UEtheriAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UEtheriAttributeSet, MaxMana, OldMaxMana);
}