// Shoot Them Up Game. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "STUBasePickups.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHEMUP_API ASTUBasePickups : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTUBasePickups();

protected:
    UPROPERTY(VisibleAnywhere, Category="Pickups")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere,BlueprintReadWrite, Category="Pickups")
    float RespawnTime = 5.0f;
    
	virtual void BeginPlay() override;
    virtual  void NotifyActorBeginOverlap(AActor* OtherActor) override;

public:	
	virtual void Tick(float DeltaTime) override;
    
private:
    virtual bool GivePickupTo(APawn* PlayerPawn);
    void PickupWasTaken();
    void Respawn();
};
