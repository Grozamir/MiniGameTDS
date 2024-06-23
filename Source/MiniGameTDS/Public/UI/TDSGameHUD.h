// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "TDSDeathScreenWidget.h"
#include "TDSInventoryWidget.h"
#include "TDSPauseWidget.h"
#include "TDSPlayerWidget.h"
#include "GameFramework/HUD.h"
#include "TDSGameHUD.generated.h"

UCLASS()
class MINIGAMETDS_API ATDSGameHUD : public AHUD
{
    GENERATED_BODY()

public:
    UTDSInventoryWidget* GetInventoryWidget() const { return InventoryWidget; }

protected:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UTDSInventoryWidget> InventoryWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UTDSPlayerWidget> PlayerWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UTDSPauseWidget> PauseWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UTDSDeathScreenWidget> DeathScreenWidgetClass;

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    UTDSInventoryWidget* InventoryWidget;

    UPROPERTY()
    UTDSPlayerWidget* PlayerWidget;

    UPROPERTY()
    UTDSPauseWidget* PauseWidget;

    UPROPERTY()
    UTDSDeathScreenWidget* DeathScreenWidget;

    UFUNCTION()
    void OpenCloseInventoryWidget(bool IsOpen) const;

    UFUNCTION()
    void OpenClosePauseWidget(bool IsOpen) const;

    UFUNCTION()
    void OpenDeathScreen() const;
};
