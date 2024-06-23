// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TDSCoreTypes.h"
#include "GameFramework/Actor.h"
#include "TDSBaseWeapon.generated.h"

class UTDSWeaponItemDataAsset;
struct FTDSItemInfo;
class ATDSBaseWeapon;

DECLARE_MULTICAST_DELEGATE(FOnAmmoWeaponEmptySignature)

UCLASS()
class MINIGAMETDS_API ATDSBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ATDSBaseWeapon();

    FOnAmmoWeaponEmptySignature OnAmmoWeaponEmpty;

    void ChangeDataWeapon(FTDSItemInfo* WeaponItemInfo);

    void UnequipWeapon();

public:
    ETDSTypeAmmo GetTypeAmmo() const;
    void ChangeAmmoWeaponToMax() const;

public:
    virtual void StartFire();
    virtual void StopFire();

private:
    FTimerHandle ShootTimer;

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* WeaponMeshComponent;

private:
    FTDSItemInfo* WeaponInfo;

    UPROPERTY()
    UTDSWeaponItemDataAsset* CurrentWeaponDataAsset = TYPE_OF_NULLPTR();

private:
    void SpawnBullet() const;
};
