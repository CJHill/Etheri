// Copyright. Hillz Studios


#include "GAS/ModMagCalc/MMC_MaxHealth.h"
#include "GAS/EtheriAttributeSet.h"
#include "Interface/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef.AttributeToCapture = UEtheriAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	VigorDef.bSnapshot = false;

	RelevantAttributesToCapture.Add(VigorDef);
}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& EffectSpec) const
{
	//Gather Tags from source and target
	const FGameplayTagContainer* sourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* targetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters evaluationParams;
	evaluationParams.SourceTags = sourceTags;
	evaluationParams.TargetTags = targetTags;

	//GetCapturedAttributeMagnitude sets this vigor variable by passing in the value of VigorDef's magnitude
	float vigor = 0.f;

	GetCapturedAttributeMagnitude(VigorDef, EffectSpec, evaluationParams, vigor);
	vigor = FMath::Max<float>(vigor, 0);

	ICombatInterface* combatInterface = Cast<ICombatInterface>(EffectSpec.GetContext().GetSourceObject());
	const int32 playerLevel = combatInterface->GetLevel();

	return 80.f + 2.5f * vigor + 10 * playerLevel;
}
