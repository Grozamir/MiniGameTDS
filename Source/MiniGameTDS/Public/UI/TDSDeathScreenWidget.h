// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDSDeathScreenWidget.generated.h"

class UButton;

UCLASS()
class MINIGAMETDS_API UTDSDeathScreenWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UButton* LoadButton;

protected:
    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnLoadClicked();
};
