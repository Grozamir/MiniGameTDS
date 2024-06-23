// Mini Game TDS. All Rights Reserved.

#include "UI/TDSItemInInventoryWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTDSItemInInventoryWidget::SetNameItem(const FText& Text) const
{
    if (!NameItemTextBlock) return;
    NameItemTextBlock->SetText(Text);
}

void UTDSItemInInventoryWidget::SetVisibleEquipButton(const bool IsVisible) const
{
    EquipItemButton->SetVisibility(IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UTDSItemInInventoryWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (DropItemButton)
    {
        DropItemButton->OnClicked.AddDynamic(this, &UTDSItemInInventoryWidget::OnDropItemClicked);
    }

    if (EquipItemButton)
    {
        EquipItemButton->OnClicked.AddDynamic(this, &UTDSItemInInventoryWidget::OnEquip);
    }
}

void UTDSItemInInventoryWidget::OnDropItemClicked()
{
    LambdaOnDrop.Execute();
}

void UTDSItemInInventoryWidget::OnEquip()
{
    LambdaOnEquip.Execute();
}
