// Copyright. Hillz Studios


#include "GAS/AbilityTask/TargetDataUnderMouse.h"
#include "AbilitySystemComponent.h"


UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* targetDataObject = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return targetDataObject;
}

void UTargetDataUnderMouse::Activate()
{
	const bool bIsLocallyControlled = Ability->GetCurrentActorInfo()->IsLocallyControlled();
	if (bIsLocallyControlled)
	{
		SendMouseCursorData();
	}
	else
	{
		//TO DO We are on the server here
	}
	
}

void UTargetDataUnderMouse::SendMouseCursorData()
{
	FScopedPredictionWindow ScopedPrediction(AbilitySystemComponent.Get());

	APlayerController* playerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult cursorHit;
	playerController->GetHitResultUnderCursor(ECC_Visibility, false, cursorHit);

	FGameplayAbilityTargetDataHandle dataHandle;
	FGameplayAbilityTargetData_SingleTargetHit* data_SingleTargetHit = new FGameplayAbilityTargetData_SingleTargetHit();

	data_SingleTargetHit->HitResult = cursorHit;
	dataHandle.Add(data_SingleTargetHit);

	AbilitySystemComponent->ServerSetReplicatedTargetData(GetAbilitySpecHandle(), GetActivationPredictionKey(), dataHandle, FGameplayTag(), AbilitySystemComponent->ScopedPredictionKey);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		ValidData.Broadcast(dataHandle);
	}

}
