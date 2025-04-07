// Copyright. Hillz Studios


#include "GAS/ModMagCalc/MMC_MaxMana.h"
#include "GAS/EtheriAttributeSet.h"
#include "Interface/CombatInterface.h"

UMMC_MaxMana::UMMC_MaxMana()
{
	IntelligenceDef.AttributeToCapture = UEtheriAttributeSet::GetIntelligenceAttribute();
	IntelligenceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	IntelligenceDef.bSnapshot = false;
}

float UMMC_MaxMana::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& EffectSpec) const
{
	//Gather Tags from source and target
	const FGameplayTagContainer* sourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* targetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters evaluationParams;
	evaluationParams.SourceTags = sourceTags;
	evaluationParams.TargetTags = targetTags;

	//GetCapturedAttributeMagnitude sets this Intelligence variable by passing in the value of IntelligenceDef's magnitude
	float intelligence;

	GetCapturedAttributeMagnitude(IntelligenceDef, EffectSpec, evaluationParams, intelligence);
	intelligence = FMath::Max<float>(intelligence, 0);

	ICombatInterface* combatInterface = Cast<ICombatInterface>(EffectSpec.GetContext().GetSourceObject());
	const int32 playerLevel = combatInterface->GetLevel();

	return 80.f + 2.5f * intelligence + 10 * playerLevel;
}
