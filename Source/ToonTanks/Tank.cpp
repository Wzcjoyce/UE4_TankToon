// Zuocheng Wang 2022


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);
}



void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if(TankPlayerController)
    {
        FHitResult HitResult;
        // get FHitResult
        TankPlayerController->GetHitResultUnderCursor
        (
            ECollisionChannel::ECC_Visibility,
            false,
            HitResult
        );

        //DrawDebugSphere
        /*
        DrawDebugSphere
        (
            GetWorld(), 
            HitResult.ImpactPoint,
            25.f,
            12,
            FColor::Red,
            false,
            -1.f
        );
        */

        RotateTurret(HitResult.ImpactPoint);
    }

}

void ATank::HandleDestruction()
{
    //inherit from the BasePawn method
    Super::HandleDestruction();

    // hide the tank actor and disable its tick
    SetActorHiddenInGame(true);
    SetActorTickEnabled(false);
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    //GetController() return AController pointer 
    // which need to be casted to APlayerController pointer
    TankPlayerController = (APlayerController*)GetController();

    // another way of cast in Unreal
    //PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

void ATank::Move(float Value)
{
    // parameter value is set in project setting -> input ->axis mappings ->scale
    //UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value)


    //This chunk of code is for moving a pawn in its local space
    //key method call is AddActorLocalOffset(FVector)
    
    // Speed control: X = Value * DeltaTime * Speed
    // UGameplayStatics::GetWorldDeltaSeconds(this)  parameter is World Context Object

    FVector DeltaLocation = FVector::ZeroVector;
	DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value)
{
    // parameter value is set in project setting -> input ->axis mappings ->scale
    //UE_LOG(LogTemp, Warning, TEXT("Value: %f"), Value)


    //This chunk of code is for turning a pawn in its local space
    //key method call is AddActorLocalRotation(FRotator)

    // Turn control: X = Value * DeltaTime * TurnRate
    // UGameplayStatics::GetWorldDeltaSeconds(this)  parameter is World Context Object

    FRotator DeltaRotation = FRotator::ZeroRotator;
	DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
	AddActorLocalRotation(DeltaRotation, true);
}

