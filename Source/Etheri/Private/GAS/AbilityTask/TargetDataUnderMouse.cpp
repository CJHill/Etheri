// Copyright. Hillz Studios


#include "GAS/AbilityTask/TargetDataUnderMouse.h"


UTargetDataUnderMouse* UTargetDataUnderMouse::CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility)
{
	UTargetDataUnderMouse* targetDataObject = NewAbilityTask<UTargetDataUnderMouse>(OwningAbility);
	return targetDataObject;
}

void UTargetDataUnderMouse::Activate()
{
	APlayerController* playerController = Ability->GetCurrentActorInfo()->PlayerController.Get();
	FHitResult cursorHit;
	playerController->GetHitResultUnderCursor(ECC_Visibility, false, cursorHit);
	ValidData.Broadcast(cursorHit.Location);
}
