// Mini Game TDS. All Rights Reserved.

#include "Player/TDSPlayerCharacter.h"

#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Components/TDSHealthComponent.h"
#include "Components/TDSWeaponComponent.h"

#include "Inventory/TDSInventoryComponent.h"
#include "Item/TDSHealthItemDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Pickups/TDSItemPickup.h"
#include "Save/TDSPlayerSaveGame.h"

ATDSPlayerCharacter::ATDSPlayerCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->TargetArmLength = 1200.0f;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponents");
    CameraComponent->SetupAttachment(SpringArmComponent);

    InventoryComponent = CreateDefaultSubobject<UTDSInventoryComponent>("InventoryComponent");
}

void ATDSPlayerCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    USkeletalMeshComponent* MeshComponent = GetMesh();
    if (!MeshComponent || !GetWorld())
    {
        return;
    }
    FVector2D MousePosition;

    GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePosition.X, MousePosition.Y);

    FVector2D ScreenSize;
    GEngine->GameViewport->GetViewportSize(ScreenSize);
    ScreenSize /= 2.0f;

    auto NormalizeMousePos = ScreenSize - MousePosition;
    NormalizeMousePos.Normalize();

    const auto RotationZ = FMath::Atan2(NormalizeMousePos.X, NormalizeMousePos.Y);

    auto NewRotation = MeshComponent->GetComponentRotation();
    NewRotation.Yaw = RotationZ * 180.0 / PI * -1.0;
    MeshComponent->SetWorldRotation(NewRotation);
}

void ATDSPlayerCharacter::Save()
{
    if (UTDSPlayerSaveGame* SaveGameInstance =
            Cast<UTDSPlayerSaveGame>(UGameplayStatics::CreateSaveGameObject(UTDSPlayerSaveGame::StaticClass())))
    {
        SaveGameInstance->Location = GetActorLocation();
        SaveGameInstance->Health = HealthComponent->GetHealth();

        InventoryComponent->SaveInventory(SaveGameInstance);

        UGameplayStatics::SaveGameToSlot(SaveGameInstance, "Player", 0);
    }
}

void ATDSPlayerCharacter::Load()
{
    if (const UTDSPlayerSaveGame* LoadedGame = Cast<UTDSPlayerSaveGame>(UGameplayStatics::LoadGameFromSlot("Player", 0)))
    {
        SetActorLocation(LoadedGame->Location);

        HealthComponent->SetHealth(LoadedGame->Health);
        InventoryComponent->LoadInventory(LoadedGame);
    }
}

void ATDSPlayerCharacter::SetTargetPickupItem(ATDSItemPickup* NewTargetPickupItem)
{
    TargetPickupItem = NewTargetPickupItem;  // can add container for PickupItems, then if player stands on a lot of picks up item
}

void ATDSPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    if (const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* InputSystem =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
        {
            if (!InputMapping.IsNull())
            {
                InputSystem->AddMappingContext(InputMapping.LoadSynchronous(), 0);
            }
        }
    }
}

void ATDSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

    EnhancedInputComponent->BindAction(InputMove, ETriggerEvent::Triggered, this, &ATDSPlayerCharacter::Move);
    EnhancedInputComponent->BindAction(InputPickup, ETriggerEvent::Triggered, this, &ATDSPlayerCharacter::PickupItem);
    EnhancedInputComponent->BindAction(InputOpenCloseInventory, ETriggerEvent::Triggered, this, &ATDSPlayerCharacter::OpenCloseInventory);

    EnhancedInputComponent->BindAction(InputShoot, ETriggerEvent::Started, this, &ATDSPlayerCharacter::StartShoot);
    EnhancedInputComponent->BindAction(InputShoot, ETriggerEvent::Completed, this, &ATDSPlayerCharacter::StopShoot);

    EnhancedInputComponent->BindAction(InputSelectFirstWeapon, ETriggerEvent::Triggered, this, &ATDSPlayerCharacter::SelectFirstWeapon);
    EnhancedInputComponent->BindAction(InputSelectSecondWeapon, ETriggerEvent::Triggered, this, &ATDSPlayerCharacter::SelectSecondWeapon);

    EnhancedInputComponent->BindAction(InputHeal, ETriggerEvent::Started, this, &ATDSPlayerCharacter::Heal);

    EnhancedInputComponent->BindAction(InputPause, ETriggerEvent::Started, this, &ATDSPlayerCharacter::Pause);
}

void ATDSPlayerCharacter::OnHealthChanged(float Health, float MaxHealth)
{
    if (Health <= 0.0f)
    {
        OnOpenDeathScreenSignature.Execute();
    }
}

void ATDSPlayerCharacter::PickupItem(const FInputActionInstance& Instance)
{
    if (TargetPickupItem)
    {
        UGameplayStatics::PlaySound2D(GetWorld(), PickupSound);

        TargetPickupItem->PickToInventory(InventoryComponent);
        TargetPickupItem = TYPE_OF_NULLPTR();
    }
}

void ATDSPlayerCharacter::OpenCloseInventory(const FInputActionInstance& Instance)
{
    if (GetWorld()->GetTimeSeconds() - LastPressedOpenClosedInventory > 0.3f)
    {
        LastPressedOpenClosedInventory = GetWorld()->GetTimeSeconds();
    }
    else
    {
        return;
    }

    IsOpenedInventory = !IsOpenedInventory;
    OnOpenCloseInventorySignature.Execute(IsOpenedInventory);
    if (IsOpenedInventory)
    {
        InventoryComponent->OnUpdateDataInventorySignature.Broadcast(InventoryComponent);
    }
}

void ATDSPlayerCharacter::Move(const FInputActionInstance& Instance)
{
    const auto AxisValue = Instance.GetValue().Get<FVector2D>();

    AddMovementInput(GetActorForwardVector(), AxisValue.X);
    AddMovementInput(GetActorRightVector(), AxisValue.Y);
}

void ATDSPlayerCharacter::StartShoot(const FInputActionInstance& Instance)
{
    WeaponComponent->StartFire();
}

void ATDSPlayerCharacter::StopShoot(const FInputActionInstance& Instance)
{
    WeaponComponent->StopFire();
}

void ATDSPlayerCharacter::SelectFirstWeapon(const FInputActionInstance& Instance)
{
    WeaponComponent->ChangeSlotWeapon(true);
}

void ATDSPlayerCharacter::SelectSecondWeapon(const FInputActionInstance& Instance)
{
    WeaponComponent->ChangeSlotWeapon(false);
}

void ATDSPlayerCharacter::Heal(const FInputActionInstance& Instance)
{
    UTDSHealthItemDataAsset* MedKitItem = TYPE_OF_NULLPTR();

    auto IndexMedKit = InventoryComponent->TryGetMedKit(&MedKitItem);

    if (IndexMedKit == INDEX_NONE)
    {
        return;
    }
    InventoryComponent->RemoveItem(IndexMedKit, false);
    HealthComponent->Heal(MedKitItem->AddedHealth);
}

void ATDSPlayerCharacter::Pause(const FInputActionInstance& Instance)
{
    const auto PlayerController = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

    if (!PlayerController)
    {
        return;
    }
    OnOpenClosePauseSignature.Execute(true);
    PlayerController->SetPause(true);
}
