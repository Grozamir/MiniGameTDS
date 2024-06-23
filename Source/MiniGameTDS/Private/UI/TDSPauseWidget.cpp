// Mini Game TDS. All Rights Reserved.

#include "UI/TDSPauseWidget.h"

#include "TDSGameInstance.h"
#include "Components/Button.h"

void UTDSPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (SaveButton)
    {
        SaveButton->OnClicked.AddDynamic(this, &UTDSPauseWidget::OnSaveClicked);
    }

    if (LoadButton)
    {
        LoadButton->OnClicked.AddDynamic(this, &UTDSPauseWidget::OnLoadClicked);
    }
}

void UTDSPauseWidget::OnSaveClicked()
{
    if (auto GameInstance = Cast<UTDSGameInstance>(GetGameInstance()))
    {
        GameInstance->SaveWorld();
    }
}

void UTDSPauseWidget::OnLoadClicked()
{
    if (auto GameInstance = Cast<UTDSGameInstance>(GetGameInstance()))
    {
        GameInstance->LoadWorld();
    }
}
