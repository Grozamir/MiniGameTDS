// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Item/TDSBaseItemDataAsset.h"
#include "TDSItemPickerSaveGame.generated.h"

class ATDSItemPickup;

USTRUCT()
struct FItemPickerSaveData
{
    GENERATED_BODY()

    UPROPERTY()
    FVector Location;

    UPROPERTY()
    UTDSBaseItemDataAsset* BaseItemDataAsset;

    UPROPERTY()
    bool IsNewItemPickup;

    UPROPERTY()
    int32 CurrentResourceAmount;
};

UCLASS()
class MINIGAMETDS_API UTDSItemPickerSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY()
    TArray<FItemPickerSaveData> ItemPickups;

    UPROPERTY()
    TSubclassOf<ATDSItemPickup> ItemPickupClass;
};
