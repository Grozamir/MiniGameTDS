// Mini Game TDS. All Rights Reserved.

#include "Character/TDSBaseCharacter.h"

#include "Components/TDSWeaponComponent.h"
#include "Components/TDSHealthComponent.h"

ATDSBaseCharacter::ATDSBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = true;

    WeaponComponent = CreateDefaultSubobject<UTDSWeaponComponent>("WeaponComponent");

    WeaponPlaceComponent = CreateDefaultSubobject<USceneComponent>("WeaponPlaceComponent");
    WeaponPlaceComponent->SetupAttachment(GetMesh());

    HealthComponent = CreateDefaultSubobject<UTDSHealthComponent>("HealthComponent");
    HealthComponent->OnHealthChanged.AddUObject(this, &ATDSBaseCharacter::OnHealthChanged);
}

void ATDSBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

void ATDSBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void ATDSBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATDSBaseCharacter::OnHealthChanged(float Health, float MaxHealth)
{
    if (Health <= 0.0f)
    {
        Destroy();
    }
}
