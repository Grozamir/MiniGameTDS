// Mini Game TDS. All Rights Reserved.

#include "UI/TDSInventoryWidget.h"

#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"

#include "Inventory/TDSInventoryComponent.h"
#include "Item/TDSBaseItemDataAsset.h"
#include "Item/TDSWeaponItemDataAsset.h"
#include "Player/TDSPlayerCharacter.h"
#include "UI/TDSItemInInventoryWidget.h"

void UTDSInventoryWidget::NativeConstruct()
{
    Super::NativeConstruct();

    const auto Character = Cast<ATDSPlayerCharacter>(GetOwningPlayerPawn());

    if (!Character)
    {
        return;
    }

    const auto InventoryComp = Character->GetInventoryComponent();

    InventoryComp->OnUpdateDataInventorySignature.AddUObject(this, &UTDSInventoryWidget::UpdateItemsInInventory);
    UnequipItemSlot_1_Btn->OnClicked.AddDynamic(InventoryComp, &UTDSInventoryComponent::UnequipItemSlot_1);
    UnequipItemSlot_2_Btn->OnClicked.AddDynamic(InventoryComp, &UTDSInventoryComponent::UnequipItemSlot_2);
}

void UTDSInventoryWidget::UpdateItemsInInventory(UTDSInventoryComponent* InventoryComponent)
{
    if (GetVisibility() == ESlateVisibility::Hidden || !ItemsScrollBox || !ItemInInventoryWidgetClass) return;

    ItemsScrollBox->ClearChildren();

    auto ItemDataAssets = InventoryComponent->GetItemDataAssets();
    for (int32 i = 0; i < ItemDataAssets.Num(); ++i)
    {
        const auto ItemSlot = CreateWidget<UTDSItemInInventoryWidget>(GetWorld(), ItemInInventoryWidgetClass);

        bool IsVisibleEquipBtn = false;

        if (ItemDataAssets[i].ItemDataAsset->TypeItem == ETDSTypeItem::Weapon)
        {
            const auto WeaponInfoDA = Cast<UTDSWeaponItemDataAsset>(ItemDataAssets[i].ItemDataAsset);
            if (WeaponInfoDA->TypeAmmo == ETDSTypeAmmo::Carbine && InventoryComponent->IsSlot_1_Free() ||
                WeaponInfoDA->TypeAmmo == ETDSTypeAmmo::Pistol && InventoryComponent->IsSlot_2_Free())
            {
                ItemSlot->LambdaOnEquip.BindLambda([=]() { InventoryComponent->EquipWeapon(i); });
                IsVisibleEquipBtn = true;
            }

            ItemSlot->SetNameItem(FText::FromString(
                ItemDataAssets[i].ItemDataAsset->ItemName + " x" + FString::FromInt(ItemDataAssets[i].CurrentResourceAmount)));
        }
        else
        {
            ItemSlot->SetNameItem(FText::FromString(ItemDataAssets[i].ItemDataAsset->ItemName));
        }

        ItemSlot->LambdaOnDrop.BindLambda([=]() { InventoryComponent->RemoveItem(i); });
        ItemSlot->SetVisibleEquipButton(IsVisibleEquipBtn);

        ItemsScrollBox->AddChild(ItemSlot);
    }

    UpdateInfoSlotsWeapon(InventoryComponent);
}

void UTDSInventoryWidget::UpdateInfoSlotsWeapon(const UTDSInventoryComponent* InventoryComponent)
{
    if (!InventoryComponent->IsSlot_1_Free())
    {
        const auto InfoSlot = InventoryComponent->GetSlot_1_ItemInfo();
        NameItemSlot_1->SetText(FText::FromString(InfoSlot.ItemDataAsset->ItemName));
        UnequipItemSlot_1_Btn->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        UnequipItemSlot_1_Btn->SetVisibility(ESlateVisibility::Hidden);
        NameItemSlot_1->SetText(FText::FromString("Empty"));
    }

    if (!InventoryComponent->IsSlot_2_Free())
    {
        const auto InfoSlot = InventoryComponent->GetSlot_2_ItemInfo();
        NameItemSlot_2->SetText(FText::FromString(InfoSlot.ItemDataAsset->ItemName));
        UnequipItemSlot_2_Btn->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        UnequipItemSlot_2_Btn->SetVisibility(ESlateVisibility::Hidden);
        NameItemSlot_2->SetText(FText::FromString("Empty"));
    }
}
