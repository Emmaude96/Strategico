#include "TurnManager.h"
#include "UnitBase.h"
#include "EngineUtils.h"

ATurnManager::ATurnManager()
{
    PrimaryActorTick.bCanEverTick = false;
    bPlayerTurn = true;
}

void ATurnManager::StartPlayerTurn()
{
    bPlayerTurn = true;
    for (TActorIterator<AUnitBase> It(GetWorld()); It; ++It)
    {
        if (It->bIsPlayerUnit)
        {
            It->StartTurn(true);
        }
    }
}

void ATurnManager::StartAITurn()
{
    bPlayerTurn = false;
    for (TActorIterator<AUnitBase> It(GetWorld()); It; ++It)
    {
        if (!It->bIsPlayerUnit)
        {
            It->StartTurn(false);
            It->FindAndMoveToEnemy();
        }
    }
}

void ATurnManager::EndCurrentTurn()
{
    if (bPlayerTurn)
    {
        StartAITurn();
    }
    else
    {
        StartPlayerTurn();
    }
}