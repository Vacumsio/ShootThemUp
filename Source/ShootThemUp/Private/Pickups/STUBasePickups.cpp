// Shoot Them Up Game. All rights reserved.


#include "Pickups/STUBasePickups.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All)

ASTUBasePickups::ASTUBasePickups()
{
	PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

void ASTUBasePickups::BeginPlay()
{
	Super::BeginPlay();

    check(CollisionComponent);

    GenerateRotationYaw();
}

void ASTUBasePickups::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickupTo(Pawn))
    {
        PickupWasTaken();
    }
}

void ASTUBasePickups::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
}

bool ASTUBasePickups::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void ASTUBasePickups::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(false,true);
    }

    FTimerHandle RespawnTimeHandle;
    GetWorldTimerManager().SetTimer(RespawnTimeHandle,this,&ASTUBasePickups::Respawn,RespawnTime);
}

void ASTUBasePickups::Respawn()
{
    GenerateRotationYaw();

    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if (GetRootComponent())
    {
        GetRootComponent()->SetVisibility(true,true);
    }
}

void ASTUBasePickups::GenerateRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
    RotationYaw = FMath::RandRange(1.0f,2.0f) * Direction;
    UE_LOG(LogBasePickup, Display, TEXT("Rotation started"));
}
