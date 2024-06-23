// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TDSGameInstance.generated.h"

UCLASS()
class MINIGAMETDS_API UTDSGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    void SaveWorld();
    void LoadWorld();
};
