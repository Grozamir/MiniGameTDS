// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TDSCoreTypes.h"
#include "TDSBaseItemDataAsset.generated.h"

UCLASS()
class MINIGAMETDS_API UTDSBaseItemDataAsset : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    FString ItemName;

    UPROPERTY(EditAnywhere)
    ETDSTypeItem TypeItem;

    UPROPERTY(EditAnywhere)
    TSoftObjectPtr<UStaticMesh> ItemStaticMesh;

    virtual FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("AssetItems", GetFName()); }
};
