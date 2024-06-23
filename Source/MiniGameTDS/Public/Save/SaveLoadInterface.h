// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SaveLoadInterface.generated.h"

UINTERFACE(MinimalAPI, Blueprintable)
class USaveLoadInterface : public UInterface
{
    GENERATED_BODY()
};

class ISaveLoadInterface
{
    GENERATED_BODY()

public:
    virtual void Save() {}
    virtual void Load() {}
};