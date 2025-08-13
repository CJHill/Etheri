// Copyright. Hillz Studios

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EtheriProjectile.generated.h"


class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
class ETHERI_API AEtheriProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEtheriProjectile();

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> ProjectileSphere;
	
};
