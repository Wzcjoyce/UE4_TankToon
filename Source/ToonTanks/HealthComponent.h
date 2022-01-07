// Zuocheng Wang 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(EditAnyWhere)
	float DamageToPlayerTank = 10.f;

	UPROPERTY(EditAnyWhere)
	float DamageToFinalEnemyTower = 20.f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnyWhere)
	float MaxHealth = 100.f;
	float Health = 100.f;

	class ATank* Tank;

	//handling damage
	UFUNCTION()
	void DamageTaken(
		AActor* DamagedActor,
		 float Damage,
		  const UDamageType* DamageType,
		   class AController* Instigator,
		   AActor* DamageCauser);

	class AToonTanksGameMode * ToonTanksGameMode;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
