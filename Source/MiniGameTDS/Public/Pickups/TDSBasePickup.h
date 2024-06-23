// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDSBasePickup.generated.h"

class USphereComponent;

UCLASS()
class MINIGAMETDS_API ATDSBasePickup : public AActor
{
    GENERATED_BODY()

public:
    ATDSBasePickup();

    virtual void Pick();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* CollisionComponent;

protected:
    virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
    virtual void EnterPickupZone(APawn* PlayerPawn);
    virtual void ExitPickupZone(APawn* PlayerPawn);
};
