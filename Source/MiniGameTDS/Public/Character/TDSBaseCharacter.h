// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TDSBaseCharacter.generated.h"

class UTDSHealthComponent;
class UTDSWeaponComponent;

UCLASS()
class MINIGAMETDS_API ATDSBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ATDSBaseCharacter();

public:
    USceneComponent* GetWeaponPlaceComponent() const { return WeaponPlaceComponent; }

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTDSWeaponComponent* WeaponComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USceneComponent* WeaponPlaceComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTDSHealthComponent* HealthComponent;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
    virtual void OnHealthChanged(float Health, float MaxHealth);
};
