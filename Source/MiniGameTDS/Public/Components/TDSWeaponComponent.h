// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDSWeaponComponent.generated.h"

class ATDSBaseWeapon;
struct FTDSItemInfo;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MINIGAMETDS_API UTDSWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTDSWeaponComponent();

public:
    void StartFire();
    void StopFire();
    void Reload();

    void ChangeWeapon(FTDSItemInfo* WeaponInfo, bool IsFirstSlotWeapon);
    void ChangeSlotWeapon(bool IsFirstSlotWeapon);

    void UnequipWeapon(bool IsFirstSlotWeapon);

    bool GetCurrentWeaponItemInfo(FTDSItemInfo& UIData);

protected:
    void OnEmptyWeaponAmmo();
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ATDSBaseWeapon* WeaponActor;

private:
    bool IsSelectedFirstSlotWeapon = true;

    FTDSItemInfo* Slot1WeaponItemInfo = TYPE_OF_NULLPTR();
    FTDSItemInfo* Slot2WeaponItemInfo = TYPE_OF_NULLPTR();
};
