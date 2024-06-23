// Mini Game TDS. All Rights Reserved.

#include "Weapon/TDSBulletProjectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Item/TDSWeaponItemDataAsset.h"
#include "Engine/DamageEvents.h"

ATDSBulletProjectile::ATDSBulletProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
    ProjectileMovementComponent->InitialSpeed = 4000.0f;
    ProjectileMovementComponent->MaxSpeed = 4000.0f;
    ProjectileMovementComponent->ProjectileGravityScale = 0.1f;

    BulletMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("BulletMeshComponent");
    BulletMeshComponent->SetCollisionProfileName("Bullet");
}

void ATDSBulletProjectile::ChangeBullet(UStaticMesh* MeshBullet) const
{
    BulletMeshComponent->SetStaticMesh(MeshBullet);
}

void ATDSBulletProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    OtherActor->TakeDamage(25.0f, FDamageEvent{}, nullptr, nullptr);

    DestroyBullet();
}

void ATDSBulletProjectile::BeginPlay()
{
    Super::BeginPlay();

    GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ATDSBulletProjectile::DestroyBullet, TimeToDestroy, false);
}

void ATDSBulletProjectile::DestroyBullet()
{
    Destroy();
}
