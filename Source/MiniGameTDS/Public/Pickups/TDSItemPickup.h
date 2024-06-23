// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Pickups/TDSBasePickup.h"
#include "TDSItemPickup.generated.h"

class UTDSInventoryComponent;
class UTDSBaseItemDataAsset;
class UStaticMeshComponent;
struct FTDSItemInfo;

UCLASS()
class MINIGAMETDS_API ATDSItemPickup : public ATDSBasePickup
{
    GENERATED_BODY()

public:
    ATDSItemPickup();

    void PickToInventory(UTDSInventoryComponent* InventoryComponent);

    void InitItem(const FTDSItemInfo& ItemInfo);

    void InitItemOnLoad(UTDSBaseItemDataAsset* NewBaseItemDataAsset, bool NewIsNewItemPickup, int32 NewCurrentResourceAmount);

public:
    UTDSBaseItemDataAsset* GetBaseItemDataAsset() const { return BaseItemDataAsset; }
    bool GetIsNewItemPickup() const { return IsNewItemPickup; }
    int32 GetCurrentResourceAmount() const { return CurrentResourceAmount; }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TSubclassOf<ATDSItemPickup> ItemPickupClass;

protected:
    UPROPERTY(EditAnywhere, Category = "Item")
    UTDSBaseItemDataAsset* BaseItemDataAsset = TYPE_OF_NULLPTR();

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* StaticMeshComponent;

private:
    bool IsNewItemPickup = true;  // if true then inventory get max value
    int32 CurrentResourceAmount;  // This for example use, for weapon current ammo or current amount of gasoline in the canister

private:
    virtual void EnterPickupZone(APawn* PlayerPawn) override;

    void UpdateStaticMesh() const;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};
