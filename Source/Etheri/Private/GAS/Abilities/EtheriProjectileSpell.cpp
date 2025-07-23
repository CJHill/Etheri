// Copyright. Hillz Studios


#include "GAS/Abilities/EtheriProjectileSpell.h"
#include "GAS/Abilities/EtheriProjectile.h"
#include "Interface/CombatInterface.h"


void UEtheriProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	
}

void UEtheriProjectileSpell::SpawnProjectile()
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();

	if (!bIsServer) return;

	ICombatInterface* combatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo());
	if (combatInterface)
	{
		const FVector socketLocation = combatInterface->GetWeaponSocketLocation();

		FTransform spawnTransform;
		spawnTransform.SetLocation(socketLocation);
		//TO DO: Set Projectile Rotation

		AEtheriProjectile* projectileToSpawn = GetWorld()->SpawnActorDeferred<AEtheriProjectile>(
			ProjectileClass,
			spawnTransform,
			GetOwningActorFromActorInfo(),
			Cast<APawn>(GetOwningActorFromActorInfo()),
			ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

		//TO DO: Give Projectile Game Effec tSpec to cause damage

		projectileToSpawn->FinishSpawning(spawnTransform);
	}

}
