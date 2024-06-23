// Mini Game TDS. All Rights Reserved.

#include "Enemy/TDSTurret.h"

#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/TDSPlayerCharacter.h"

#include "Components/TDSHealthComponent.h"
#include "Weapon/TDSBulletProjectile.h"

ATDSTurret::ATDSTurret()
{
    PrimaryActorTick.bCanEverTick = true;

    TurretMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("TurretMeshComponent");
    TurretMeshComponent->SetupAttachment(GetRootComponent());

    PointShootComponent = CreateDefaultSubobject<USceneComponent>("PointShootComponent");
    PointShootComponent->SetupAttachment(TurretMeshComponent);

    HealthComponent = CreateDefaultSubobject<UTDSHealthComponent>("HealthComponent");
    HealthComponent->OnHealthChanged.AddUObject(this, &ATDSTurret::OnHealthChanged);

    ZoneAttackTriggerComponent = CreateDefaultSubobject<USphereComponent>("ZoneAttackTriggerComponent");
    ZoneAttackTriggerComponent->InitSphereRadius(400.0f);
    ZoneAttackTriggerComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    ZoneAttackTriggerComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    ZoneAttackTriggerComponent->SetupAttachment(TurretMeshComponent);
}

bool ATDSTurret::IsAttacking()
{
    if (TargetShoot)
    {
        return true;
    }
    return false;
}

void ATDSTurret::InitOnLoad(float Health, bool IsAttackPlayer)
{
    HealthComponent->SetHealth(Health);
    if (IsAttackPlayer)
    {
        TargetShoot = GetWorld()->GetFirstPlayerController()->GetCharacter();
        StartShoot();
    }
}

void ATDSTurret::BeginPlay()
{
    Super::BeginPlay();
}

void ATDSTurret::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TargetShoot)
    {
        const auto NewRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetShoot->GetActorLocation());
        SetActorRotation(NewRotation);
    }
}

void ATDSTurret::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto PlayerCharacter = Cast<ATDSPlayerCharacter>(OtherActor);
    if (PlayerCharacter)
    {
        TargetShoot = OtherActor;
        StartShoot();
    }
}

void ATDSTurret::StartShoot()
{
    GetWorldTimerManager().SetTimer(ShootTimer, this, &ATDSTurret::SpawnBullet, 0.5f, true);
}

void ATDSTurret::SpawnBullet()
{
    const auto BulletTransform = PointShootComponent->GetComponentTransform();
    const FVector Location = BulletTransform.GetLocation();
    const FRotator Rotation = BulletTransform.GetRotation().Rotator();
    const FActorSpawnParameters SpawnInfo;

    const auto Bullet = GetWorld()->SpawnActor<ATDSBulletProjectile>(ATDSBulletProjectile::StaticClass(), Location, Rotation, SpawnInfo);
    Bullet->ChangeBullet(BulletStaticMesh.LoadSynchronous());
}

void ATDSTurret::OnHealthChanged(float Health, float MaxHealth)
{
    if (Health <= 0.0f)
    {
        Destroy();
    }
    else
    {
        TargetShoot = GetWorld()->GetFirstPlayerController()->GetCharacter();
        StartShoot();
    }
}
