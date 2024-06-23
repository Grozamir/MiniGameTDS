// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDSCoreTypes.h"
#include "Pickups/TDSItemPickup.h"

#include "TDSInventoryComponent.generated.h"

class UTDSPlayerSaveGame;
class UTDSHealthItemDataAsset;
class UTDSBaseItemDataAsset;
class UTDSInventoryComponent;
class ATDSItemPickup;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnUpdateDataInventorySignature, UTDSInventoryComponent*)

    UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class MINIGAMETDS_API UTDSInventoryComponent
    : public UActorComponent
{
    GENERATED_BODY()

public:
    UTDSInventoryComponent();

public:
    void SaveInventory(UTDSPlayerSaveGame* SaveGameInstance);
    void LoadInventory(const UTDSPlayerSaveGame* LoadedGame);

protected:
    virtual void BeginPlay() override;

public:
    UPROPERTY(EditAnywhere)
    TSubclassOf<ATDSItemPickup> ItemPickupActorClass = ATDSItemPickup::StaticClass();

public:
    void AddItem(UTDSBaseItemDataAsset* ItemDataAsset, bool IsHaveCurrentValue, int32 CurrentValueItem = 0);
    void RemoveItem(int32 Index, bool IsDropped = true);

    FOnUpdateDataInventorySignature OnUpdateDataInventorySignature;

public:
    void EquipWeapon(int32 Index);

    UFUNCTION()
    void UnequipItemSlot_1();

    UFUNCTION()
    void UnequipItemSlot_2();

    const TArray<FTDSItemInfo>& GetItemDataAssets() { return ItemsInfo; }
    const FTDSItemInfo& GetSlot_1_ItemInfo() const { return Slot_1_ItemInfo; }
    const FTDSItemInfo& GetSlot_2_ItemInfo() const { return Slot_2_ItemInfo; }

    bool IsSlot_1_Free() const { return Slot_1_ItemInfo.ItemDataAsset == TYPE_OF_NULLPTR(); }
    bool IsSlot_2_Free() const { return Slot_2_ItemInfo.ItemDataAsset == TYPE_OF_NULLPTR(); }

    bool ReloadWeapon(ETDSTypeAmmo NeededTypeAmmo);

public:
    int32 TryGetMedKit(UTDSHealthItemDataAsset** HealthItem);

private:
    FTDSItemInfo Slot_1_ItemInfo;
    FTDSItemInfo Slot_2_ItemInfo;

    TArray<FTDSItemInfo> ItemsInfo;
};
