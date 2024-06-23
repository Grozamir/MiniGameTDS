// Mini Game TDS. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TDSHealthComponent.h"
#include "GameFramework/Actor.h"
#include "TDSTurret.generated.h"

class UTDSHealthComponent;
class USphereComponent;

UCLASS()
class MINIGAMETDS_API ATDSTurret : public AActor
{
    GENERATED_BODY()

public:
    ATDSTurret();

public:
    float GetHealth() const { return HealthComponent->GetHealth(); }
    bool IsAttacking();

    void InitOnLoad(float Health, bool IsAttackPlayer);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TSubclassOf<ATDSTurret> TurretClass;

protected:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UStaticMeshComponent* TurretMeshComponent;

    UPROPERTY(Instanced, VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTDSHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USceneComponent* PointShootComponent;

    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    USphereComponent* ZoneAttackTriggerComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
    TSoftObjectPtr<UStaticMesh> BulletStaticMesh;

public:
    virtual void Tick(float DeltaTime) override;

    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
    UPROPERTY()
    AActor* TargetShoot = TYPE_OF_NULLPTR();

private:
    FTimerHandle ShootTimer;

    void StartShoot();
    void SpawnBullet();

private:
    void OnHealthChanged(float Health, float MaxHealth);
};
