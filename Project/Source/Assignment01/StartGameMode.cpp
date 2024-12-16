// Fill out your copyright notice in the Description page of Project Settings.

#include "Blueprint/UserWidget.h"
#include "StartGameMode.h"

AStartGameMode::AStartGameMode()
{
	DefaultPawnClass = nullptr;
}

void AStartGameMode::BeginPlay()
{
    Super::BeginPlay();

    if (MainMenuClass) // 检查主界面蓝图类是否设置
    {
        UUserWidget* MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuClass);
        if (MainMenuWidget)
        {
            MainMenuWidget->AddToViewport();
            GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(true); // 显示鼠标
        }
    }
}
