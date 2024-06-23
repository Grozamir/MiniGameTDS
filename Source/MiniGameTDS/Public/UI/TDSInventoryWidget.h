// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDSInventoryWidget.generated.h"

class UTextBlock;
class UScrollBox;
class UTDSInventoryComponent;
class UButton;

UCLASS()
class MINIGAMETDS_API UTDSInventoryWidget : public UUserWidget
{
    GENERATED_BODY()

protected:
    UPROPERTY(meta = (BindWidget))
    UScrollBox* ItemsScrollBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> ItemInInventoryWidgetClass;

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* NameItemSlot_1;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* NameItemSlot_2;

    UPROPERTY(meta = (BindWidget))
    UButton* UnequipItemSlot_1_Btn;

    UPROPERTY(meta = (BindWidget))
    UButton* UnequipItemSlot_2_Btn;

protected:
    virtual void NativeConstruct() override;

public:
    UFUNCTION()
    void UpdateItemsInInventory(UTDSInventoryComponent* InventoryComponent);

    UFUNCTION()
    void UpdateInfoSlotsWeapon(const UTDSInventoryComponent* InventoryComponent);
};
