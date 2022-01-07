//  Zuocheng Wang 2022


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Pawn contain a RootComponent by default which is a USceneComponent
	// However, We can assign a capsule to RootComponent for handling collision
	// Since USceneComponent support attachment, 
	// we can also attach other mesh to BaseMesh (static mesh components)

	//In this case Pawn's RootComponent is Ucapsule Component
	// Turrent and tank is static mesh component
	// projectile point is UsceneComponent

	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	
	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	//TODO Visual and sound effects

	if(DealthParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
		this,
		DealthParticles,
		GetActorLocation(),
		GetActorRotation()
		);
	}

	if(DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			DeathSound,
			GetActorLocation()
		);
	}

	if(DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass);
	}
}


void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	// vector calculation: ToTarget = target - current 
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	TurretMesh->SetWorldRotation(LookAtRotation);

}


void ABasePawn::Fire()
{
	FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	FRotator ProjectileSpawnPointRotation = ProjectileSpawnPoint->GetComponentRotation();

	//get the pointer to the spawn actor
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnPointLocation, ProjectileSpawnPointRotation);

	// set the owner of spawned projectile to BasePawn
	Projectile->SetOwner(this);
	/*
	DrawDebugSphere
        (
            GetWorld(), 
            ProjectileSpawnPointLocation,
            25.f,
            12,
            FColor::Red,
            false,
            3.f
        );
	*/
}