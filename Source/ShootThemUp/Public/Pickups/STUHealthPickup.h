// Shoot Them Up Game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/STUBasePickups.h"
#include "STUHealthPickup.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUBasePickups
{
	GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Pickups", meta=(ClampMin="1.0",ClampMax="100.0"))
    float HealthAmount = 50.0f;
    
private:
    virtual bool GivePickupTo(APawn* PlayerPawn) override;
};
