// Zuocheng Wang 2022


#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "ToonTanksGameMode.h"


// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;

	Tank = (ATank*)(UGameplayStatics::GetPlayerPawn(this, 0));

	// Important!!!!!!!********************************
	// Similar to the Hit Event in Projectile.cpp
	// Bind he OnTakeAnyDamage to the Owner
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
	ToonTanksGameMode = Cast<AToonTanksGameMode>(UGameplayStatics::GetGameMode(this));
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::DamageTaken(
		AActor* DamagedActor,
		 float Damage,
		  const UDamageType* DamageType,
		   class AController* Instigator,
		   AActor* DamageCauser)
{

	if(Damage <= 0.f)
	{
		return;
	}

	if(Tank == (ATank*)DamagedActor)
	{
		Health -= DamageToPlayerTank;
		ToonTanksGameMode->SetHealthBar(Health);
		UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health);
	}
	else if(ToonTanksGameMode->TargetTowers == 1)
	{
		Health -= DamageToFinalEnemyTower;
	}
	else
	{
		Health -= Damage;
	}


	if(Health <= 0.f && ToonTanksGameMode)
	{
		ToonTanksGameMode->ActorDied(DamagedActor);
	}

}

