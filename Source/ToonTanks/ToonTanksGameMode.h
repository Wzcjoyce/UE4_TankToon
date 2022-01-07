// Zuocheng Wang 2022

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	void ActorDied(AActor* DeadActor);
	int32 TargetTowers = 15;

	void SetHealthBar(float Health);


protected:

	virtual void BeginPlay() override;

	//to setup Start game Widget on screen 
	// edit in Event Graph
	UFUNCTION(BlueprintImplementableEvent)
	void StartGame();

	UFUNCTION(BlueprintImplementableEvent)
	void GameOver(bool bWonGame);

	UFUNCTION(BlueprintImplementableEvent)
	void HandleHealthBarAndEnemyLeft(float Health, int32 EnemyLeft);




private:

	class ATank* Tank;
	class AToonTanksPlayerController* ToonTanksPlayerController;
	float StartDelay = 3.f;

	void HandleGameStart();
	int32 GetTargetTowerCount();

	int32 CurrentHealth;
	
	UPROPERTY(EditAnyWhere, Category = "Combat")
	USoundBase* VictorySound;
};
