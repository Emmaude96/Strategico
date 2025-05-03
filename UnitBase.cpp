#include "UnitBase.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "Kismet/KismetMathLibrary.h"

AUnitBase::AUnitBase()
{
    PrimaryActorTick.bCanEverTick = false;

    UnitMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("UnitMesh"));
    RootComponent = UnitMesh;

    Health = 100;
    MaxMove = 3;
    AttackRange = 1;
    MinDamage = 5;
    MaxDamage = 10;
    bIsPlayerUnit = true;
    bHasMoved = false;
    bHasAttacked = false;
    AttackType = EAttackType::Melee;
}

void AUnitBase::BeginPlay()
{
    Super::BeginPlay();
}

void AUnitBase::MoveUnit(FVector NewLocation)
{
    if (!bHasMoved && IsValidMove(NewLocation))
    {
        SetActorLocation(NewLocation);
        bHasMoved = true;
    }
}

bool AUnitBase::IsValidMove(FVector TargetLocation)
{
    float Distance = FVector::Dist(GetActorLocation(), TargetLocation);
    return Distance <= MaxMove * 100.0f;
}

void AUnitBase::AttackUnit(AUnitBase* Target)
{
    if (!bHasAttacked && Target && Target->Health > 0)
    {
        float Distance = FVector::Dist(GetActorLocation(), Target->GetActorLocation());

        if (Distance <= AttackRange * 100.0f)
        {
            int32 Damage = FMath::RandRange(MinDamage, MaxDamage);
            Target->TakeDamage(Damage);
            bHasAttacked = true;

            if (Target->AttackType == EAttackType::Melee && Distance <= 100.0f && Target->Health > 0)
            {
                int32 Counter = FMath::RandRange(1, 3);
                TakeDamage(Counter);
            }
        }
    }
}

void AUnitBase::TakeDamage(int32 Damage)
{
    Health -= Damage;
    if (Health <= 0) Destroy();
}

void AUnitBase::EndTurn()
{
    bHasMoved = false;
    bHasAttacked = false;
}

void AUnitBase::StartTurn(bool bIsPlayerTurn)
{
    if (bIsPlayerUnit == bIsPlayerTurn)
    {
        EndTurn();
    }
}

void AUnitBase::AIMoveToEnemy(AUnitBase* EnemyUnit)
{
    if (EnemyUnit)
    {
        FVector Direction = (EnemyUnit->GetActorLocation() - GetActorLocation()).GetSafeNormal();
        FVector MovePos = GetActorLocation() + Direction * MaxMove * 100.0f;
        MoveUnit(MovePos);
    }
}

AUnitBase* AUnitBase::GetClosestEnemy(TArray<AUnitBase*> EnemyUnits)
{
    float ClosestDist = TNumericLimits<float>::Max();
    AUnitBase* Closest = nullptr;

    for (AUnitBase* Enemy : EnemyUnits)
    {
        if (!Enemy || Enemy->Health <= 0) continue;
        float Dist = FVector::Dist(GetActorLocation(), Enemy->GetActorLocation());
        if (Dist < ClosestDist)
        {
            ClosestDist = Dist;
            Closest = Enemy;
        }
    }

    return Closest;
}

void AUnitBase::FindAndMoveToEnemy()
{
    TArray<AUnitBase*> Enemies;

    for (TActorIterator<AUnitBase> It(GetWorld()); It; ++It)
    {
        if (It->bIsPlayerUnit != bIsPlayerUnit)
        {
            Enemies.Add(*It);
        }
    }

    AUnitBase* Closest = GetClosestEnemy(Enemies);
    if (Closest)
    {
        AIMoveToEnemy(Closest);
    }
}

TArray<FVector> AUnitBase::CalculatePath(FVector Start, FVector Goal)
{
    TArray<FVector> Path;
    Path.Add(Goal);
    return Path;
}