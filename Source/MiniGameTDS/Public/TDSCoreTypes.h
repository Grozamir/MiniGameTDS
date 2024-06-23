#pragma once

#include "TDSCoreTypes.generated.h"

class UTDSBaseItemDataAsset;

// Items

UENUM(BlueprintType)
enum class ETDSTypeItem : uint8
{
    Weapon = 0,
    MedKit,
    Ammo
};

UENUM(BlueprintType)
enum class ETDSTypeAmmo : uint8
{
    Carbine = 0,
    Pistol
};

UENUM(BlueprintType)
enum class ETDSTypeShooting : uint8
{
    SingleShots = 0,
    FiringBursts
};

USTRUCT(BlueprintType)
struct FTDSItemInfo
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    UTDSBaseItemDataAsset* ItemDataAsset = TYPE_OF_NULLPTR();

    UPROPERTY(BlueprintReadWrite)
    int32 CurrentResourceAmount = -1;
};
