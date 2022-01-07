//  Zuocheng Wang 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	// UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	// allow access and edit in event graph

	void HandleDestruction();


protected:

	void RotateTurret(FVector LookAtTarget);
	void Fire();


private:
	//forward declaration because we only need a pointer to this class here
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, CateGory = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, CateGory = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite, CateGory = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh;

	
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, CateGory = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint;

	UPROPERTY(EditAnyWhere, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass;

	//handle death
	UPROPERTY(EditAnyWhere, Category = "Combat")
	class UParticleSystem* DealthParticles;


	UPROPERTY(EditAnyWhere, Category = "Combat")
	USoundBase* DeathSound;

	
	UPROPERTY(EditAnyWhere, Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass;
};
