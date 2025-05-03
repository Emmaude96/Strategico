#include "GameManager.h"
#include "Kismet/GameplayStatics.h"
#include "UnitBase.h"
#include "EngineUtils.h"

AGameManager::AGameManager()
{
    bIsPlayerTurn = true;
}

void AGameManager::BeginPlay()
{
    Super::BeginPlay();
    StartGame();
}

void AGameManager::StartGame()
{
    bIsPlayerTurn = FMath::RandBool();
    for (TActorIterator<AUnitBase> It(GetWorld()); It; ++It)
    {
        It->StartTurn(bIsPlayerTurn == It->bIsPlayerUnit);
    }
}

void AGameManager::EndTurn()
{
    bIsPlayerTurn = !bIsPlayerTurn;
    for (TActorIterator<AUnitBase> It(GetWorld()); It; ++It)
    {
        It->StartTurn(bIsPlayerTurn == It->bIsPlayerUnit);
    }
    CheckGameOver();
}

void AGameManager::CheckGameOver()
{
    bool bPlayerAlive = false;
    bool bEnemyAlive = false;

    for (TActorIterator<AUnitBase> It(GetWorld()); It; ++It)
    {
        if (It->Health > 0)
        {
            if (It->bIsPlayerUnit)
                bPlayerAlive = true;
            else
                bEnemyAlive = true;
        }
    }

    if (!bPlayerAlive || !bEnemyAlive)
    {
        FString Winner = bPlayerAlive ? TEXT("Player Wins!") : TEXT("AI Wins!");
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, Winner);
        UGameplayStatics::SetGamePaused(GetWorld(), true);
    }
}