// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Item/TDSBaseItemDataAsset.h"
#include "TDSWeaponItemDataAsset.generated.h"

UCLASS()
class MINIGAMETDS_API UTDSWeaponItemDataAsset : public UTDSBaseItemDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere)
    int32 MaxAmmo;

    UPROPERTY(EditAnywhere)
    FName MuzzleSocketName;

    UPROPERTY(EditAnywhere)
    ETDSTypeAmmo TypeAmmo;

    UPROPERTY(EditAnywhere)
    ETDSTypeShooting TypeShooting;

    UPROPERTY(EditAnywhere)
    TSoftObjectPtr<UStaticMesh> BulletStaticMesh;
};
