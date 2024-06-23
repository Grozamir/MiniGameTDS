// Mini Game TDS. All Rights Reserved.

#include "TDSGameInstance.h"

#include "Enemy/TDSTurret.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Pickups/TDSItemPickup.h"

#include "Save/SaveLoadInterface.h"
#include "Save/TDSBaseEnemySaveGame.h"
#include "Save/TDSItemPickerSaveGame.h"

void UTDSGameInstance::SaveWorld()
{
    if (const auto SaveObj = Cast<ISaveLoadInterface>(GetFirstGamePlayer()->GetPlayerController(GetWorld())->GetCharacter()))
    {
        SaveObj->Save();
    }

    {  // Pickup Items
        TArray<AActor*> ItemPickupsActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATDSItemPickup::StaticClass(), ItemPickupsActors);

        if (UTDSItemPickerSaveGame* SaveGameInstance =
                Cast<UTDSItemPickerSaveGame>(UGameplayStatics::CreateSaveGameObject(UTDSItemPickerSaveGame::StaticClass())))
        {
            for (auto ItemPickupActor : ItemPickupsActors)
            {
                auto ItemPickup = Cast<ATDSItemPickup>(ItemPickupActor);
                SaveGameInstance->ItemPickups.Add({ItemPickupActor->GetActorLocation(), ItemPickup->GetBaseItemDataAsset(),
                    ItemPickup->GetIsNewItemPickup(), ItemPickup->GetCurrentResourceAmount()});
            }

            if (ItemPickupsActors.IsEmpty() != true)
            {
                SaveGameInstance->ItemPickupClass = Cast<ATDSItemPickup>(ItemPickupsActors.Last())->ItemPickupClass;
            }

            UGameplayStatics::SaveGameToSlot(SaveGameInstance, "ItemPickups", 0);
        }
    }

    {  // Enemies
        TArray<AActor*> TurretActors;
        UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATDSTurret::StaticClass(), TurretActors);

        if (UTDSBaseEnemySaveGame* SaveGameInstance =
                Cast<UTDSBaseEnemySaveGame>(UGameplayStatics::CreateSaveGameObject(UTDSBaseEnemySaveGame::StaticClass())))
        {
            for (auto TurretActor : TurretActors)
            {
                auto Turret = Cast<ATDSTurret>(TurretActor);
                SaveGameInstance->BaseEnemies.Add({TurretActor->GetActorLocation(), Turret->GetHealth(), Turret->IsAttacking()});
            }
            if (TurretActors.IsEmpty() != true)
            {
                SaveGameInstance->TurretClass = Cast<ATDSTurret>(TurretActors.Last())->TurretClass;
            }

            UGameplayStatics::SaveGameToSlot(SaveGameInstance, "BaseEnemies", 0);
        }
    }
}

void UTDSGameInstance::LoadWorld()
{
    if (const auto SaveObj = Cast<ISaveLoadInterface>(GetFirstGamePlayer()->GetPlayerController(GetWorld())->GetCharacter()))
    {
        SaveObj->Load();
    }

    if (const UTDSItemPickerSaveGame* LoadedGame = Cast<UTDSItemPickerSaveGame>(UGameplayStatics::LoadGameFromSlot("ItemPickups", 0)))
    {
        {
            TArray<AActor*> ItemPickupsActors;
            UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATDSItemPickup::StaticClass(), ItemPickupsActors);

            for (auto ItemPickupActor : ItemPickupsActors)
            {
                ItemPickupActor->Destroy();
            }
        }
        for (auto ItemPickup : LoadedGame->ItemPickups)
        {
            ATDSItemPickup* ItemPickupActor = GetWorld()->SpawnActor<ATDSItemPickup>(LoadedGame->ItemPickupClass);
            ItemPickupActor->SetActorLocation(ItemPickup.Location);
            ItemPickupActor->InitItemOnLoad(ItemPickup.BaseItemDataAsset, ItemPickup.IsNewItemPickup, ItemPickup.CurrentResourceAmount);
        }
    }

    if (const UTDSBaseEnemySaveGame* LoadedGame = Cast<UTDSBaseEnemySaveGame>(UGameplayStatics::LoadGameFromSlot("BaseEnemies", 0)))
    {
        {
            TArray<AActor*> TurretActors;
            UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATDSTurret::StaticClass(), TurretActors);

            for (auto TurretActor : TurretActors)
            {
                TurretActor->Destroy();
            }
        }
        for (auto Enemy : LoadedGame->BaseEnemies)
        {
            ATDSTurret* EnemyActor = GetWorld()->SpawnActor<ATDSTurret>(LoadedGame->TurretClass);
            EnemyActor->SetActorLocation(Enemy.Location);
            EnemyActor->InitOnLoad(Enemy.Health, Enemy.IsAttackPlayer);
        }
    }
}
