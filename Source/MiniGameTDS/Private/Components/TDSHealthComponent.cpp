// Mini Game TDS. All Rights Reserved.

#include "Components/TDSHealthComponent.h"

UTDSHealthComponent::UTDSHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

bool UTDSHealthComponent::GetHealthUIInfo(float& HealthInfo, float& MaxHealthInfo)
{
    HealthInfo = Health;
    MaxHealthInfo = MaxHealth;
    return true;
}

void UTDSHealthComponent::Heal(float AddedHealth)
{
    Health = FMath::Clamp(Health + AddedHealth, 0.0f, MaxHealth);
}

void UTDSHealthComponent::SetHealth(const float NewHealth)
{
    Health = NewHealth;
}

void UTDSHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;

    if (const auto Owner = GetOwner())
    {
        Owner->OnTakeAnyDamage.AddDynamic(this, &UTDSHealthComponent::OnTakeAnyDamage);
    }
}

void UTDSHealthComponent::OnTakeAnyDamage(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    Health -= Damage;

    OnHealthChanged.Broadcast(Health, MaxHealth);
}
