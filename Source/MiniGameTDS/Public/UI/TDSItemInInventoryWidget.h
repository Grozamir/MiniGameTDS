// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDSItemInInventoryWidget.generated.h"

class UTextBlock;
class UButton;

DECLARE_DELEGATE(FLambdaOnEquipSignature)

UCLASS()
class MINIGAMETDS_API UTDSItemInInventoryWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    void SetNameItem(const FText& Text) const;

    void SetVisibleEquipButton(bool IsVisible) const;

    FLambdaOnEquipSignature LambdaOnEquip;
    FLambdaOnEquipSignature LambdaOnDrop;

protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock* NameItemTextBlock;

    UPROPERTY(meta = (BindWidget))
    UButton* DropItemButton;

    UPROPERTY(meta = (BindWidget))
    UButton* EquipItemButton;

protected:
    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnDropItemClicked();

    UFUNCTION()
    void OnEquip();
};
