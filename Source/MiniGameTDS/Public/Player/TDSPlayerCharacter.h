// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/TDSBaseCharacter.h"
#include "Save/SaveLoadInterface.h"
#include "TDSPlayerCharacter.generated.h"

class ATDSItemPickup;
class USpringArmComponent;
class UCameraComponent;
class UTDSInventoryComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionInstance;

DECLARE_DELEGATE_OneParam(FOnOpenCloseInventorySignature, bool);
DECLARE_DELEGATE_OneParam(FOnOpenClosePauseSignature, bool);
DECLARE_DELEGATE(FOnOpenDeathScreenSignature);

UCLASS() class MINIGAMETDS_API ATDSPlayerCharacter : public ATDSBaseCharacter, public ISaveLoadInterface
{
    GENERATED_BODY()

public:
    ATDSPlayerCharacter();

    virtual void Tick(float DeltaTime) override;

public:
    virtual void Save() override;
    virtual void Load() override;

public:
    void SetTargetPickupItem(ATDSItemPickup* NewTargetPickupItem);

    UTDSInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

public:
    FOnOpenCloseInventorySignature OnOpenCloseInventorySignature;
    FOnOpenClosePauseSignature OnOpenClosePauseSignature;
    FOnOpenDeathScreenSignature OnOpenDeathScreenSignature;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTDSInventoryComponent* InventoryComponent;

protected:
    UPROPERTY(EditAnywhere, Category = "Sounds")
    USoundBase* PickupSound;

protected:
    UPROPERTY(EditAnywhere, Category = "Input")
    TSoftObjectPtr<UInputMappingContext> InputMapping;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* InputMove;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* InputPickup;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* InputOpenCloseInventory;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* InputShoot;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* InputSelectFirstWeapon;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* InputSelectSecondWeapon;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* InputHeal;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* InputPause;

protected:
    virtual void BeginPlay() override;

public:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
    virtual void OnHealthChanged(float Health, float MaxHealth) override;

private:
    UPROPERTY()
    ATDSItemPickup* TargetPickupItem = TYPE_OF_NULLPTR();

    void PickupItem(const FInputActionInstance& Instance);

private:
    bool IsOpenedInventory = false;
    double LastPressedOpenClosedInventory = 0.0;
    void OpenCloseInventory(const FInputActionInstance& Instance);

private:
    void Move(const FInputActionInstance& Instance);

private:
    void StartShoot(const FInputActionInstance& Instance);
    void StopShoot(const FInputActionInstance& Instance);

private:
    void SelectFirstWeapon(const FInputActionInstance& Instance);
    void SelectSecondWeapon(const FInputActionInstance& Instance);

private:
    void Heal(const FInputActionInstance& Instance);

private:
    void Pause(const FInputActionInstance& Instance);
};
