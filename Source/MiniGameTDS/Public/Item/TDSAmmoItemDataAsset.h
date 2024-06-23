// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Item/TDSBaseItemDataAsset.h"
#include "TDSAmmoItemDataAsset.generated.h"

UCLASS()
class MINIGAMETDS_API UTDSAmmoItemDataAsset : public UTDSBaseItemDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    ETDSTypeAmmo TypeAmmo;

    UPROPERTY(EditAnywhere)
    int32 MaxCountAmmo;
};
