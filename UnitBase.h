#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UnitBase.generated.h"

UENUM(BlueprintType)
enum class EAttackType : uint8
{
    Melee,
    Ranged
};

UCLASS()
class STRATEGICO_API AUnitBase : public AActor
{
    GENERATED_BODY()

public:
    AUnitBase();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* UnitMesh;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 Health;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 MaxMove;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 AttackRange;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 MinDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    int32 MaxDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    bool bIsPlayerUnit;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
    EAttackType AttackType;

    UPROPERTY(BlueprintReadWrite)
    bool bHasMoved;

    UPROPERTY(BlueprintReadWrite)
    bool bHasAttacked;

    void MoveUnit(FVector NewLocation);
    void AttackUnit(AUnitBase* Target);
    void TakeDamage(int32 Damage);
    void EndTurn();
    bool IsValidMove(FVector TargetLocation);
    void StartTurn(bool bIsPlayerTurn);

    void AIMoveToEnemy(AUnitBase* EnemyUnit);
    void FindAndMoveToEnemy();
    AUnitBase* GetClosestEnemy(TArray<AUnitBase*> EnemyUnits);
    void MoveToPosition(FVector TargetPosition);
    TArray<FVector> CalculatePath(FVector Start, FVector Goal);

protected:
    virtual void BeginPlay() override;
};