#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridManager.generated.h"

UCLASS()
class STRATEGICO_API AGridManager : public AActor
{
    GENERATED_BODY()

public:
    AGridManager();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
    int32 GridSize;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
    float CellSize;

    UFUNCTION(BlueprintCallable)
    FVector GetWorldPositionFromGrid(int32 Row, int32 Col);

protected:
    virtual void BeginPlay() override;
};