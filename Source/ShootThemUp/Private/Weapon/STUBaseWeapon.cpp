// Shoot Them Up Game. All rights reserved.

#include "Weapon/STUBaseWeapon.h"
#include <Components/SkeletalMeshComponent.h>

ASTUBaseWeapon::ASTUBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASTUBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}
