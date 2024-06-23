// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TDSCoreTypes.h"
#include "GameFramework/SaveGame.h"
#include "TDSPlayerSaveGame.generated.h"

UCLASS()
class MINIGAMETDS_API UTDSPlayerSaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY()
    FVector Location;

    UPROPERTY()
    float Health;

    UPROPERTY()
    FTDSItemInfo Slot_1_ItemInfo{TYPE_OF_NULLPTR()};

    UPROPERTY()
    FTDSItemInfo Slot_2_ItemInfo{TYPE_OF_NULLPTR()};

    UPROPERTY()
    TArray<FTDSItemInfo> ItemsInfo;
};
