#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGameWidget.generated.h"

UCLASS()
class STRATEGICO_API UEndGameWidget : public UUserWidget
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "EndGame")
    void DisplayResult(bool bPlayerWon);
};