// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDSPlayerWidget.generated.h"

struct FTDSItemInfo;

UCLASS()
class MINIGAMETDS_API UTDSPlayerWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponAmmoData(FTDSItemInfo& WeaponInfo) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetHealthData(float& Health, float& MaxHealth) const;
};
