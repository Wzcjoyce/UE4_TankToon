// Zuocheng Wang 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, CateGory = "Combat", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* ProjectileMesh;

	UPROPERTY(VisibleAnywhere, CateGory = "Movement", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;

	//handle on hit
	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComp,
		 AActor* OtherActor,
		  UPrimitiveComponent* OtherComp,
		   FVector NormalImpulse,
		   const FHitResult& Hit);
	
	UPROPERTY(EditAnyWhere)
	float Damage = 50.f;

	//handle smoke
	UPROPERTY(EditAnyWhere, Category = "Combat")
	class UParticleSystem* HitParticles;

	// handle smoke trail
	UPROPERTY(EditAnyWhere, Category = "Combat")
	class UParticleSystemComponent* TrailParticles;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	USoundBase* HitSound;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
