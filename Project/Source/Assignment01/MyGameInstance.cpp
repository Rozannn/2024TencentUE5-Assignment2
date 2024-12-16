#include "MyGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Kismet/GameplayStatics.h"

void UMyGameInstance::Init()
{
    Super::Init();
    
}

void UMyGameInstance::StartGame()
{
    //UGameplayStatics::OpenLevel(GetWorld(), FName("FirstPersonMap"));
    // ��ʾ���ؽ���
    ShowLoadingScreen();
    // ���عؿ�
    LoadGameLevel();
}

void UMyGameInstance::ShowLoadingScreen()
{
    if (CurrentWidget)
    {
        CurrentWidget->RemoveFromViewport();
    }

    if (LoadingScreenClass)
    {
        CurrentWidget = CreateWidget<UUserWidget>(this, LoadingScreenClass);
        if (CurrentWidget)
        {
            CurrentWidget->AddToViewport(9);
        }
    }
}

void UMyGameInstance::LoadGameLevel()
{
    Progress = 0.f;
    GetWorld()->GetTimerManager().SetTimer(LoadingTimerHandle, [this]() mutable {
        Progress = Progress + 0.2f;

        // ���½�����
        if (UUserWidget* LoadingWidget = CurrentWidget)
        {
            UProgressBar* ProgressBar = Cast<UProgressBar>(LoadingWidget->GetWidgetFromName("LoadingProgressBar"));
            if (ProgressBar)
            {
                ProgressBar->SetPercent(Progress);
            }
        }
        UE_LOG(LogTemp, Warning, TEXT("Timer ticked. Current Progress: %f"), Progress);
        // �������
        if (Progress >= 1.0f)
        {
            GetWorld()->GetTimerManager().ClearTimer(LoadingTimerHandle);

            // ��ת����Ϸ�ؿ�
            UGameplayStatics::OpenLevel(GetWorld(), FName("FirstPersonMap"));
        }
        }, 0.1f, true);
}
