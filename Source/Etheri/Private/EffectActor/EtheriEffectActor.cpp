// Copyright. Hillz Studios


#include "EffectActor/EtheriEffectActor.h"
#include "Components/SphereComponent.h"
#include "AbilitySystemInterface.h"
#include "GAS/EtheriAttributeSet.h"
// Sets default values
AEtheriEffectActor::AEtheriEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	EEActorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("Static Mesh");
	SetRootComponent(EEActorStaticMesh);

	EEActorSphere = CreateDefaultSubobject<USphereComponent>("Sphere");
	EEActorSphere->SetupAttachment(GetRootComponent());
	
}

void AEtheriEffectActor::OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* abilitySystemInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UEtheriAttributeSet* etheriAttributeSet = Cast<UEtheriAttributeSet>(abilitySystemInterface->GetAbilitySystemComponent()->GetAttributeSet(UEtheriAttributeSet::StaticClass()));
		UEtheriAttributeSet* mutableEtheriAttributeSet = const_cast<UEtheriAttributeSet*>(etheriAttributeSet);
		mutableEtheriAttributeSet->SetMana(etheriAttributeSet->GetMana() + 25.f);
		Destroy();
	}
}

void AEtheriEffectActor::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}


void AEtheriEffectActor::BeginPlay()
{
	Super::BeginPlay();
	EEActorSphere->OnComponentBeginOverlap.AddDynamic(this, &AEtheriEffectActor::OnOverlap);
	EEActorSphere->OnComponentEndOverlap.AddDynamic(this, &AEtheriEffectActor::EndOverlap);
}




