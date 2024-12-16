#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class ASSIGNMENT01_API UMyGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    virtual void Init() override;

    UFUNCTION(BlueprintCallable)
    void StartGame();

private:
    void ShowLoadingScreen();
    void LoadGameLevel();

    FTimerHandle LoadingTimerHandle;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> MainMenuClass;

    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<class UUserWidget> LoadingScreenClass;

    UPROPERTY()
    UUserWidget* CurrentWidget;

    float Progress;
};
