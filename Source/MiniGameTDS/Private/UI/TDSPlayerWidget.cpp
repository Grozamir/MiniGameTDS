// Mini Game TDS. All Rights Reserved.

#include "UI/TDSPlayerWidget.h"

#include "Components/TDSWeaponComponent.h"
#include "Components/TDSHealthComponent.h"

bool UTDSPlayerWidget::GetWeaponAmmoData(FTDSItemInfo& WeaponInfo) const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return false;

    const auto WeaponComponent = Cast<UTDSWeaponComponent>(Player->GetComponentByClass(UTDSWeaponComponent::StaticClass()));
    if (!WeaponComponent) return false;

    return WeaponComponent->GetCurrentWeaponItemInfo(WeaponInfo);
}

bool UTDSPlayerWidget::GetHealthData(float& Health, float& MaxHealth) const
{
    const auto Player = GetOwningPlayerPawn();
    if (!Player) return false;

    const auto HealthComponent = Cast<UTDSHealthComponent>(Player->GetComponentByClass(UTDSHealthComponent::StaticClass()));
    if (!HealthComponent) return false;

    return HealthComponent->GetHealthUIInfo(Health, MaxHealth);
}
