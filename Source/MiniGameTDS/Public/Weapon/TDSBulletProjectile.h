// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "TDSBulletProjectile.generated.h"

class UTDSWeaponItemDataAsset;
class UProjectileMovementComponent;

UCLASS()
class MINIGAMETDS_API ATDSBulletProjectile : public AActor
{
    GENERATED_BODY()

public:
    ATDSBulletProjectile();

public:
    void ChangeBullet(UStaticMesh* MeshBullet) const;

public:
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY()
    UProjectileMovementComponent* ProjectileMovementComponent;

    UPROPERTY()
    UStaticMeshComponent* BulletMeshComponent;

private:
    FTimerHandle DestroyTimerHandle;

    float TimeToDestroy = 1.5f;

    void DestroyBullet();
};
