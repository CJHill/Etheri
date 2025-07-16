// Copyright. Hillz Studios


#include "GAS/Abilities/EtheriProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AEtheriProjectile::AEtheriProjectile()
{
 	
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ProjectileSphere = CreateDefaultSubobject<USphereComponent>("Projectile Sphere");
	SetRootComponent(ProjectileSphere);
	ProjectileSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	ProjectileSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	ProjectileSphere->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	ProjectileSphere->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	ProjectileSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	ProjectileMovementComp = CreateDefaultSubobject<UProjectileMovementComponent>("Projectile Movement Component");
	ProjectileMovementComp->InitialSpeed = 550.f;
	ProjectileMovementComp->MaxSpeed = 550.f;
	ProjectileMovementComp->ProjectileGravityScale = 0.f;
}


void AEtheriProjectile::BeginPlay()
{
	Super::BeginPlay();
	ProjectileSphere->OnComponentBeginOverlap.AddDynamic(this, &AEtheriProjectile::OnSphereOverlap);
}

void AEtheriProjectile::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}


