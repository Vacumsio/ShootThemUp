// Shoot Them Up Game. All rights reserved.

#include "Weapon/STUProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

ASTUProjectile::ASTUProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    MovementComponent->ProjectileGravityScale = 0.0f;
}

void ASTUProjectile::BeginPlay()
{
    Super::BeginPlay();
    
    check(MovementComponent)
    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    SetLifeSpan(5.0f);
}
