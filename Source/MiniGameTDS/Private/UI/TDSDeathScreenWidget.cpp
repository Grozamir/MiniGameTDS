// Mini Game TDS. All Rights Reserved.

#include "UI/TDSDeathScreenWidget.h"

#include "TDSGameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UTDSDeathScreenWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (LoadButton)
    {
        LoadButton->OnClicked.AddDynamic(this, &UTDSDeathScreenWidget::OnLoadClicked);
    }
}

void UTDSDeathScreenWidget::OnLoadClicked()
{
    if (auto GameInstance = Cast<UTDSGameInstance>(GetGameInstance()))
    {
        SetVisibility(ESlateVisibility::Hidden);
        GameInstance->LoadWorld();
    }
}
