// Mini Game TDS. All Rights Reserved.

#include "Pickups/TDSItemPickup.h"

#include "Components/StaticMeshComponent.h"

#include "Item/TDSBaseItemDataAsset.h"

#include "Inventory/TDSInventoryComponent.h"
#include "Player/TDSPlayerCharacter.h"

ATDSItemPickup::ATDSItemPickup()
{
    StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
    StaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::Type::NoCollision);
    StaticMeshComponent->SetupAttachment(GetRootComponent());
}

void ATDSItemPickup::PickToInventory(UTDSInventoryComponent* InventoryComponent)
{
    InventoryComponent->AddItem(BaseItemDataAsset, !IsNewItemPickup, CurrentResourceAmount);
    Super::Pick();
}

void ATDSItemPickup::InitItem(const FTDSItemInfo& ItemInfo)
{
    BaseItemDataAsset = ItemInfo.ItemDataAsset;
    CurrentResourceAmount = ItemInfo.CurrentResourceAmount;
    IsNewItemPickup = false;
    UpdateStaticMesh();
}

void ATDSItemPickup::InitItemOnLoad(UTDSBaseItemDataAsset* NewBaseItemDataAsset, bool NewIsNewItemPickup, int32 NewCurrentResourceAmount)
{
    BaseItemDataAsset = NewBaseItemDataAsset;
    CurrentResourceAmount = NewCurrentResourceAmount;
    IsNewItemPickup = NewIsNewItemPickup;
    UpdateStaticMesh();
}

void ATDSItemPickup::EnterPickupZone(APawn* PlayerPawn)
{
    const auto Character = Cast<ATDSPlayerCharacter>(PlayerPawn->GetController()->GetCharacter());
    if (Character)
    {
        Character->SetTargetPickupItem(this);
    }
}

void ATDSItemPickup::UpdateStaticMesh() const
{
    if (BaseItemDataAsset)
    {
        StaticMeshComponent->SetStaticMesh(BaseItemDataAsset->ItemStaticMesh.LoadSynchronous());
    }
    else
    {
        StaticMeshComponent->SetStaticMesh(TYPE_OF_NULLPTR());
    }
}

#if WITH_EDITOR
void ATDSItemPickup::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);

    UpdateStaticMesh();
}
#endif
