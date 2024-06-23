// Mini Game TDS. All Rights Reserved.

#include "Pickups/TDSBasePickup.h"

#include "Components/SphereComponent.h"

ATDSBasePickup::ATDSBasePickup()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(100.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);

    SetRootComponent(CollisionComponent);
}

void ATDSBasePickup::Pick()
{
    Destroy();
}

void ATDSBasePickup::BeginPlay()
{
    Super::BeginPlay();
}

void ATDSBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (Pawn)
    {
        EnterPickupZone(Pawn);
    }
}

void ATDSBasePickup::EnterPickupZone(APawn* PlayerPawn) {}

void ATDSBasePickup::ExitPickupZone(APawn* PlayerPawn) {}
