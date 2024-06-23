// Mini Game TDS. All Rights Reserved.

#include "Inventory/TDSInventoryComponent.h"

#include "TDSCoreTypes.h"
#include "Components/TDSWeaponComponent.h"
#include "Item/TDSAmmoItemDataAsset.h"
#include "Item/TDSBaseItemDataAsset.h"
#include "Item/TDSHealthItemDataAsset.h"
#include "Item/TDSWeaponItemDataAsset.h"
#include "Pickups/TDSItemPickup.h"
#include "Save/TDSPlayerSaveGame.h"

UTDSInventoryComponent::UTDSInventoryComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UTDSInventoryComponent::SaveInventory(UTDSPlayerSaveGame* SaveGameInstance)
{
    SaveGameInstance->ItemsInfo = ItemsInfo;
    SaveGameInstance->Slot_1_ItemInfo = Slot_1_ItemInfo;
    SaveGameInstance->Slot_2_ItemInfo = Slot_2_ItemInfo;
}

void UTDSInventoryComponent::LoadInventory(const UTDSPlayerSaveGame* LoadedGame)
{
    ItemsInfo = LoadedGame->ItemsInfo;
    Slot_1_ItemInfo = LoadedGame->Slot_1_ItemInfo;
    Slot_2_ItemInfo = LoadedGame->Slot_2_ItemInfo;

    const auto WeaponComponent = GetOwner()->FindComponentByClass<UTDSWeaponComponent>();
    if (Slot_2_ItemInfo.CurrentResourceAmount != -1)
    {
        WeaponComponent->ChangeWeapon(&Slot_2_ItemInfo, false);
    }

    if (Slot_1_ItemInfo.CurrentResourceAmount != -1)
    {
        WeaponComponent->ChangeWeapon(&Slot_1_ItemInfo, true);
    }

    OnUpdateDataInventorySignature.Broadcast(this);
}

void UTDSInventoryComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UTDSInventoryComponent::AddItem(UTDSBaseItemDataAsset* ItemDataAsset, const bool IsHaveCurrentValue, const int32 CurrentValueItem)
{
    if (ItemDataAsset->TypeItem == ETDSTypeItem::Weapon)
    {
        const int32 CurrentAmmo = IsHaveCurrentValue ? CurrentValueItem : Cast<UTDSWeaponItemDataAsset>(ItemDataAsset)->MaxAmmo;
        ItemsInfo.Add({ItemDataAsset, CurrentAmmo});
    }
    else
    {
        ItemsInfo.Add({ItemDataAsset});
    }

    OnUpdateDataInventorySignature.Broadcast(this);
}

void UTDSInventoryComponent::RemoveItem(const int32 Index, const bool IsDropped)
{
    if (ItemsInfo.IsEmpty())
    {
        return;
    }

    if (IsDropped)
    {
        auto TransformItemPickup = GetOwner()->GetActorTransform();
        auto NewLocation = TransformItemPickup.GetLocation();

        constexpr double HalfHeightCharacter = 88.0;
        constexpr double OffsetX = 100.0;
        constexpr double OffsetZ = HalfHeightCharacter - 20.0;
        NewLocation.X -= OffsetX;
        NewLocation.Z -= OffsetZ;
        TransformItemPickup.SetLocation(NewLocation);

        const auto NewItemPicker = GetWorld()->SpawnActor<ATDSItemPickup>(ItemPickupActorClass, TransformItemPickup);

        NewItemPicker->InitItem(ItemsInfo[Index]);
    }

    ItemsInfo.RemoveAt(Index);
    OnUpdateDataInventorySignature.Broadcast(this);
}

void UTDSInventoryComponent::EquipWeapon(const int32 Index)
{
    const auto WeaponItemDA = Cast<UTDSWeaponItemDataAsset>(ItemsInfo[Index].ItemDataAsset);

    auto WeaponComponent = GetOwner()->FindComponentByClass<UTDSWeaponComponent>();
    if (WeaponItemDA->TypeAmmo == ETDSTypeAmmo::Carbine)
    {
        Slot_1_ItemInfo = ItemsInfo[Index];

        WeaponComponent->ChangeWeapon(&Slot_1_ItemInfo, true);
    }
    else if (WeaponItemDA->TypeAmmo == ETDSTypeAmmo::Pistol)
    {
        Slot_2_ItemInfo = ItemsInfo[Index];

        WeaponComponent->ChangeWeapon(&Slot_2_ItemInfo, false);
    }

    RemoveItem(Index, false);
}

void UTDSInventoryComponent::UnequipItemSlot_1()
{
    ItemsInfo.Add({Slot_1_ItemInfo.ItemDataAsset, Slot_1_ItemInfo.CurrentResourceAmount});
    Slot_1_ItemInfo = {TYPE_OF_NULLPTR()};

    const auto WeaponComponent = GetOwner()->FindComponentByClass<UTDSWeaponComponent>();
    WeaponComponent->UnequipWeapon(true);

    OnUpdateDataInventorySignature.Broadcast(this);
}

void UTDSInventoryComponent::UnequipItemSlot_2()
{
    ItemsInfo.Add({Slot_2_ItemInfo.ItemDataAsset, Slot_2_ItemInfo.CurrentResourceAmount});
    Slot_2_ItemInfo = {TYPE_OF_NULLPTR()};

    const auto WeaponComponent = GetOwner()->FindComponentByClass<UTDSWeaponComponent>();
    WeaponComponent->UnequipWeapon(false);

    OnUpdateDataInventorySignature.Broadcast(this);
}

bool UTDSInventoryComponent::ReloadWeapon(ETDSTypeAmmo NeededTypeAmmo)
{
    auto IndexNeededAmmo = ItemsInfo.IndexOfByPredicate(
        [&](const FTDSItemInfo& Item)
        {
            if (Item.ItemDataAsset->TypeItem == ETDSTypeItem::Ammo)
            {
                if (Cast<UTDSAmmoItemDataAsset>(Item.ItemDataAsset)->TypeAmmo == NeededTypeAmmo)
                {
                    return true;
                }
            }
            return false;
        });

    if (IndexNeededAmmo == INDEX_NONE)
    {
        return false;
    }
    RemoveItem(IndexNeededAmmo, false);

    return true;
}

int32 UTDSInventoryComponent::TryGetMedKit(UTDSHealthItemDataAsset** HealthItem)
{
    const auto IndexMedKit = ItemsInfo.IndexOfByPredicate(
        [&](const FTDSItemInfo& Item)
        {
            if (Item.ItemDataAsset->TypeItem == ETDSTypeItem::MedKit)
            {
                return true;
            }
            return false;
        });

    if (IndexMedKit != INDEX_NONE)
    {
        *HealthItem = Cast<UTDSHealthItemDataAsset>(ItemsInfo[IndexMedKit].ItemDataAsset);
    }

    return IndexMedKit;
}
