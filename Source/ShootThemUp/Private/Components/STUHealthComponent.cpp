// Shoot Them Up Game. All rights reserved.

#include "Components/STUHealthComponent.h"
#include <GameFramework/Actor.h>
#include <Engine/World.h>
#include <TimerManager.h>

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All)

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool USTUHealthComponent::TryToAddHealth(float HealthAmount)
{
    if (IsDead() || IsHealthFool()) return false;
    
    SetHealth(Health + HealthAmount);
    return true;
}

bool USTUHealthComponent::IsHealthFool() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);

    SetHealth(MaxHealth);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld())
        return;

    SetHealth(Health - Damage);
    //Health = FMath::Clamp(Health - Damage, 0.0f, MaxHealth);
    //OnHealthChanged.Broadcast(Health);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (AutoHeal)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }
}

void USTUHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if (IsHealthFool() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void USTUHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}
