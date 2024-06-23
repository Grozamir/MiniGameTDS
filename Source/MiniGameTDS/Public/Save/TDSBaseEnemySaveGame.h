// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TDSBaseEnemySaveGame.generated.h"

class ATDSTurret;

USTRUCT()
struct FBaseEnemySaveData
{
    GENERATED_BODY()

    UPROPERTY()
    FVector Location;

    UPROPERTY()
    float Health;

    UPROPERTY()
    bool IsAttackPlayer;
};

UCLASS()
class MINIGAMETDS_API UTDSBaseEnemySaveGame : public USaveGame
{
    GENERATED_BODY()

public:
    UPROPERTY()
    TArray<FBaseEnemySaveData> BaseEnemies;

    UPROPERTY()
    TSubclassOf<ATDSTurret> TurretClass;
};
