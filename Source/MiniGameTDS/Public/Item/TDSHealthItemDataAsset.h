// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Item/TDSBaseItemDataAsset.h"
#include "TDSHealthItemDataAsset.generated.h"

UCLASS()
class MINIGAMETDS_API UTDSHealthItemDataAsset : public UTDSBaseItemDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    int32 AddedHealth;
};
