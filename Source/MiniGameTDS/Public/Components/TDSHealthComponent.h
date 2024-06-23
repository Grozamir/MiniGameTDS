// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDSHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float)

    UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent)) class MINIGAMETDS_API UTDSHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UTDSHealthComponent();

public:
    FOnHealthChangedSignature OnHealthChanged;

    bool GetHealthUIInfo(float& HealthInfo, float& MaxHealthInfo);

    UFUNCTION(BlueprintCallable)
    float GetHealth() const { return Health; }

    void Heal(float AddedHealth);

    void SetHealth(const float NewHealth);

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
    float MaxHealth = 100.0f;

private:
    float Health = 0.0f;

private:
    UFUNCTION()
    void OnTakeAnyDamage(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
