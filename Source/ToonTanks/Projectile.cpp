// Zuocheng Wang 2022


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Camera/CameraShakeBase.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh;

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 2000.f;
	ProjectileMovementComponent->InitialSpeed = 2000.f;

	TrailParticles =  CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Smoke Trail"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	// Handle Onhit event
	// Important!!!!! ******************************************************
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
	
	if(LaunchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(
			this,
			LaunchSound,
			GetActorLocation()
		);
	}
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(
	UPrimitiveComponent* HitComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		FVector NormalImpulse,
		const FHitResult& Hit)
{
	//Following LOG is to check what are these parameter after Hit Event
	//UE_LOG(LogTemp, Warning, TEXT("OnHit"));
	//UE_LOG(LogTemp, Warning, TEXT("HitComp: %s"), *HitComp->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("OtherActor: %s"), *OtherActor->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("OtherComp: %s"), *OtherComp->GetName());

	// Owner was set to the BasePawn when projectile was spawned.
	auto MyOwner = GetOwner();
	if(MyOwner == nullptr) 
	{
		Destroy();	
		return;
	}

	auto MyOwnerInstigator = MyOwner->GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		//Important!!!!!!!!!!!!!!!!!
		//****************************************************************
		// when this is called, the other actor's method with this parameter format will be called
		// the method DamageTaken is in HealthComponent.cpp
		// all the Actor own a HealthComponent can be taken damage.
		UGameplayStatics::ApplyDamage(
			OtherActor,
			Damage,
			MyOwnerInstigator,
			this,
			DamageTypeClass);

		if(HitParticles)
		{
			UGameplayStatics::SpawnEmitterAtLocation(
			this,
			HitParticles,
			GetActorLocation(),
			GetActorRotation()
			);
		}

		if(HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this,
				HitSound,
				GetActorLocation()
			);
		}

		if(HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass);
		}
		
		
		Destroy();
	}


}

