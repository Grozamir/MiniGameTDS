// Mini Game TDS. All Rights Reserved.

#include "UI/TDSGameHUD.h"

#include "Player/TDSPlayerCharacter.h"

void ATDSGameHUD::BeginPlay()
{
    Super::BeginPlay();

    InventoryWidget = CreateWidget<UTDSInventoryWidget>(GetWorld(), InventoryWidgetClass);
    if (InventoryWidget)
    {
        InventoryWidget->AddToViewport();
        InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    PlayerWidget = CreateWidget<UTDSPlayerWidget>(GetWorld(), PlayerWidgetClass);
    if (PlayerWidget)
    {
        PlayerWidget->AddToViewport();
    }

    PauseWidget = CreateWidget<UTDSPauseWidget>(GetWorld(), PauseWidgetClass);
    if (PauseWidget)
    {
        PauseWidget->AddToViewport();
        PauseWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    DeathScreenWidget = CreateWidget<UTDSDeathScreenWidget>(GetWorld(), DeathScreenWidgetClass);
    if (DeathScreenWidget)
    {
        DeathScreenWidget->AddToViewport();
        DeathScreenWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    const auto Character = Cast<ATDSPlayerCharacter>(GetOwningPawn());
    if (Character)
    {
        Character->OnOpenCloseInventorySignature.BindUObject(this, &ATDSGameHUD::OpenCloseInventoryWidget);
        Character->OnOpenClosePauseSignature.BindUObject(this, &ATDSGameHUD::OpenClosePauseWidget);
        Character->OnOpenDeathScreenSignature.BindUObject(this, &ATDSGameHUD::OpenDeathScreen);
    }
}

void ATDSGameHUD::OpenCloseInventoryWidget(const bool IsOpen) const
{
    if (IsOpen)
    {
        InventoryWidget->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void ATDSGameHUD::OpenClosePauseWidget(bool IsOpen) const
{
    if (IsOpen)
    {
        PauseWidget->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        PauseWidget->SetVisibility(ESlateVisibility::Hidden);
    }
}

void ATDSGameHUD::OpenDeathScreen() const
{
    DeathScreenWidget->SetVisibility(ESlateVisibility::Visible);
}
