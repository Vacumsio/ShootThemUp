// Shoot Them Up Game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickups.h"
#include "STUHealthPickup.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickups
{
	GENERATED_BODY()

private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
