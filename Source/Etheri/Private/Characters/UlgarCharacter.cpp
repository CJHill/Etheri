// Copyright. Hillz Studios


#include "Characters/UlgarCharacter.h"
#include "DrawDebugHelpers.h"
#include "Etheri/Etheri.h"

AUlgarCharacter::AUlgarCharacter()
{
	
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
}

void AUlgarCharacter::HighlightActor()
{

	
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	GetMesh()->MarkRenderStateDirty();

	WeaponMesh->SetRenderCustomDepth(true);
	WeaponMesh->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	WeaponMesh->MarkRenderStateDirty();
}

void AUlgarCharacter::UnHighlightActor()
{

	GetMesh()->SetRenderCustomDepth(false);
	WeaponMesh->SetRenderCustomDepth(false);
}
