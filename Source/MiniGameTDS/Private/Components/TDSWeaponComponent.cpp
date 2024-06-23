// Mini Game TDS. All Rights Reserved.

#include "Components/TDSWeaponComponent.h"

#include "Character/TDSBaseCharacter.h"
#include "Inventory/TDSInventoryComponent.h"
#include "Weapon/TDSBaseWeapon.h"

UTDSWeaponComponent::UTDSWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTDSWeaponComponent::StartFire()
{
    WeaponActor->StartFire();
}

void UTDSWeaponComponent::StopFire()
{
    WeaponActor->StopFire();
}

void UTDSWeaponComponent::Reload() {}

void UTDSWeaponComponent::ChangeWeapon(FTDSItemInfo* WeaponInfo, const bool IsFirstSlotWeapon)
{
    if (IsFirstSlotWeapon)
    {
        Slot1WeaponItemInfo = WeaponInfo;
        IsSelectedFirstSlotWeapon = true;
    }
    else
    {
        Slot2WeaponItemInfo = WeaponInfo;
        IsSelectedFirstSlotWeapon = false;
    }
    WeaponActor->ChangeDataWeapon(WeaponInfo);
}

void UTDSWeaponComponent::ChangeSlotWeapon(bool IsFirstSlotWeapon)
{
    if (IsFirstSlotWeapon)
    {
        if (Slot1WeaponItemInfo != TYPE_OF_NULLPTR())
        {
            IsSelectedFirstSlotWeapon = true;
            WeaponActor->ChangeDataWeapon(Slot1WeaponItemInfo);
        }
    }
    else
    {
        if (Slot2WeaponItemInfo != TYPE_OF_NULLPTR())
        {
            IsSelectedFirstSlotWeapon = false;
            WeaponActor->ChangeDataWeapon(Slot2WeaponItemInfo);
        }
    }
}

void UTDSWeaponComponent::UnequipWeapon(bool IsFirstSlotWeapon)
{
    if (IsFirstSlotWeapon == IsSelectedFirstSlotWeapon)
    {
        WeaponActor->UnequipWeapon();
    }

    if (IsFirstSlotWeapon)
    {
        Slot1WeaponItemInfo = TYPE_OF_NULLPTR();
    }
    else
    {
        Slot2WeaponItemInfo = TYPE_OF_NULLPTR();
    }
}

bool UTDSWeaponComponent::GetCurrentWeaponItemInfo(FTDSItemInfo& UIData)
{
    if (IsSelectedFirstSlotWeapon)
    {
        if (Slot1WeaponItemInfo != TYPE_OF_NULLPTR())
        {
            UIData = *Slot1WeaponItemInfo;
            return true;
        }
        return false;
    }
    else
    {
        if (Slot2WeaponItemInfo != TYPE_OF_NULLPTR())
        {
            UIData = *Slot2WeaponItemInfo;
            return true;
        }
        return false;
    }
}

void UTDSWeaponComponent::OnEmptyWeaponAmmo()
{
    auto InventoryComponent = Cast<UTDSInventoryComponent>(GetOwner()->GetComponentByClass(UTDSInventoryComponent::StaticClass()));
    if (!InventoryComponent) return;

    if (InventoryComponent->ReloadWeapon(WeaponActor->GetTypeAmmo()))
    {
        WeaponActor->ChangeAmmoWeaponToMax();
    }
}

void UTDSWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    WeaponActor = GetWorld()->SpawnActor<ATDSBaseWeapon>();
    WeaponActor->AttachToComponent(
        Cast<ATDSBaseCharacter>(GetOwner())->GetWeaponPlaceComponent(), FAttachmentTransformRules::KeepRelativeTransform);
    WeaponActor->OnAmmoWeaponEmpty.AddUObject(this, &UTDSWeaponComponent::OnEmptyWeaponAmmo);
}
