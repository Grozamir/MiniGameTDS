// Mini Game TDS. All Rights Reserved.

#include "Weapon/TDSBaseWeapon.h"

#include "Inventory/TDSInventoryComponent.h"
#include "Item/TDSWeaponItemDataAsset.h"
#include "Weapon/TDSBulletProjectile.h"

ATDSBaseWeapon::ATDSBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;

    WeaponMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMeshComponent");
    WeaponMeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
    WeaponMeshComponent->SetupAttachment(GetRootComponent());
}

void ATDSBaseWeapon::ChangeDataWeapon(FTDSItemInfo* WeaponItemInfo)
{
    WeaponInfo = WeaponItemInfo;
    CurrentWeaponDataAsset = Cast<UTDSWeaponItemDataAsset>(WeaponInfo->ItemDataAsset);

    WeaponMeshComponent->SetStaticMesh(CurrentWeaponDataAsset->ItemStaticMesh.LoadSynchronous());
}

void ATDSBaseWeapon::UnequipWeapon()
{
    WeaponInfo = TYPE_OF_NULLPTR();
    CurrentWeaponDataAsset = TYPE_OF_NULLPTR();
    WeaponMeshComponent->SetStaticMesh(TYPE_OF_NULLPTR());
}

ETDSTypeAmmo ATDSBaseWeapon::GetTypeAmmo() const
{
    return CurrentWeaponDataAsset->TypeAmmo;
}

void ATDSBaseWeapon::ChangeAmmoWeaponToMax() const
{
    WeaponInfo->CurrentResourceAmount = CurrentWeaponDataAsset->MaxAmmo;
}

void ATDSBaseWeapon::StartFire()
{
    if (CurrentWeaponDataAsset == TYPE_OF_NULLPTR()) return;
    if (WeaponInfo->CurrentResourceAmount <= 0)
    {
        OnAmmoWeaponEmpty.Broadcast();
        return;
    }

    switch (CurrentWeaponDataAsset->TypeShooting)
    {
        case ETDSTypeShooting::SingleShots: SpawnBullet(); break;
        case ETDSTypeShooting::FiringBursts:
            SpawnBullet();
            GetWorldTimerManager().SetTimer(ShootTimer, this, &ATDSBaseWeapon::SpawnBullet, 0.15f, true);
            break;
    }
}

void ATDSBaseWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShootTimer);
}

void ATDSBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}

void ATDSBaseWeapon::SpawnBullet() const
{
    if (WeaponInfo->CurrentResourceAmount <= 0) return;
    --WeaponInfo->CurrentResourceAmount;

    const auto BulletTransform = WeaponMeshComponent->GetSocketTransform(CurrentWeaponDataAsset->MuzzleSocketName);
    const FVector Location = BulletTransform.GetLocation();
    const FRotator Rotation = BulletTransform.GetRotation().Rotator();
    const FActorSpawnParameters SpawnInfo;

    const auto Bullet = GetWorld()->SpawnActor<ATDSBulletProjectile>(ATDSBulletProjectile::StaticClass(), Location, Rotation, SpawnInfo);
    Bullet->ChangeBullet(CurrentWeaponDataAsset->BulletStaticMesh.LoadSynchronous());

    if (WeaponInfo->CurrentResourceAmount <= 0)
    {
        OnAmmoWeaponEmpty.Broadcast();
    }
}
