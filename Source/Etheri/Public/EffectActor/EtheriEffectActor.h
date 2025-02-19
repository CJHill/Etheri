// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EtheriEffectActor.generated.h"

class USphereComponent;

UCLASS()
class ETHERI_API AEtheriEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEtheriEffectActor();
	UFUNCTION()
	virtual void OnOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> EEActorSphere;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> EEActorStaticMesh;
public:	
	

};
