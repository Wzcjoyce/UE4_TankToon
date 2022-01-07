// Zuocheng Wang 2022


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "TimerManager.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{

    if(DeadActor == Tank)
    {
        Tank->HandleDestruction();
        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false);
            //Tank->DisableInput(Tank->GetTankPlayerController());
            //Tank->GetTankPlayerController()->bShowMouseCursor = false;
        }
        GameOver(false);
        
    }
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
        --TargetTowers;
        HandleHealthBarAndEnemyLeft(CurrentHealth, TargetTowers);
        if(TargetTowers == 0)
        {
            GameOver(true);
            if(VictorySound)
	        {
		        UGameplayStatics::PlaySoundAtLocation(
			    this,
			    VictorySound,
                Tank->GetActorLocation()
		    );
	}
        }
    }


}


void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();

}

void AToonTanksGameMode::HandleGameStart()
{
    CurrentHealth = 100;
    TargetTowers = GetTargetTowerCount();
    HandleHealthBarAndEnemyLeft(CurrentHealth, TargetTowers);

    Tank = (ATank*)(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = (AToonTanksPlayerController*)(UGameplayStatics::GetPlayerController(this, 0));

    StartGame();

    if(ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false);


        // When we want to pass parameter into the Call back function with timer
        // we need to use FTimerDelegate
        // In this case, we want to pass true to SetPlayerEnbaledState call back function
        // after specific time period.
        FTimerHandle PlayerEnableTimerHandle;
        FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject
        (
            ToonTanksPlayerController,
            &AToonTanksPlayerController::SetPlayerEnabledState,
            true
        ); //pass true into AToonTanksPlayerController::SetPlayerEnabledState

        GetWorldTimerManager().SetTimer
        (
            PlayerEnableTimerHandle,
            PlayerEnableTimerDelegate,
            StartDelay,
            false
        );

    }
}

int32 AToonTanksGameMode::GetTargetTowerCount()
{
    TArray<AActor*> Towers;

    UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);

    return Towers.Num();
}

void AToonTanksGameMode::SetHealthBar(float RemainedHealth)
{
    CurrentHealth = RemainedHealth;
    HandleHealthBarAndEnemyLeft(RemainedHealth, TargetTowers);
}



