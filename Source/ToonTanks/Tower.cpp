// Zuocheng Wang 2022


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ATank pointer protection
    /*
    if(Tank)
    {
        //Find the distance to the Tank
        float Distance = FVector::Dist(GetOwner()->GetActorLocation(), Tank->GetActorLocation());

        //Check to see if the Tank is in range
        if(Distance <= FireRange)
        {
            //If in range, rotate turret tower
            RotateTurret(Tank->GetActorLocation());
        }
    } */

    //refactor
    if(InFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::HandleDestruction()
{
    //inherit from the BasePawn method
    Super::HandleDestruction();
    Destroy();
}

// Called when the game starts or when spawned
void ATower::BeginPlay()
{
	Super::BeginPlay();
    
    Tank = (ATank*)(UGameplayStatics::GetPlayerPawn(this, 0));
	
    GetWorldTimerManager().SetTimer
    (
        FireRateTimerHandle, 
        this, 
        &ATower::CheckFireCondition, 
        FireRate, 
        true
    );
}

void ATower::CheckFireCondition()
{
    /*
    if(Tank)
    {
        //Find the distance to the Tank
        float Distance = FVector::Dist(GetOwner()->GetActorLocation(), Tank->GetActorLocation());

        //Check to see if the Tank is in range
        if(Distance <= FireRange)
        {
            //If in range, fire the player tank
            Fire();
        }
    } */

    //refactor
    if(InFireRange())
    {
        Fire();
    }

}

bool ATower::InFireRange()
{
    if(Tank)
    {
        //Find the distance to the Tank
        float Distance = FVector::Dist(GetOwner()->GetActorLocation(), Tank->GetActorLocation());

        //Check to see if the Tank is in range
        if(Distance <= FireRange)
        {
            //If in range, return true which means fire the player tank
            return true;
        }
    }

    return false;    

}