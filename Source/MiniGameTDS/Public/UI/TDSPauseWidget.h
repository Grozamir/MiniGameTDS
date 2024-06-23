// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDSPauseWidget.generated.h"

class UButton;

UCLASS()
class MINIGAMETDS_API UTDSPauseWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* SaveButton;

    UPROPERTY(meta = (BindWidget))
    UButton* LoadButton;

protected:
    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnSaveClicked();

    UFUNCTION()
    void OnLoadClicked();
};
