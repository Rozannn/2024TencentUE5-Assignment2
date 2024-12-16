// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"

void UMyUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (CrossHair)
    {
        CrossHair->SetColorAndOpacity(FLinearColor(0.f, 1.f, 0.f, 1.f));
    }
}

void UMyUserWidget::SetCrossHairColor(FLinearColor NewColor)
{
    if (CrossHair)
    {
        CrossHair->SetColorAndOpacity(NewColor);
    }

}

void UMyUserWidget::ResetCrossHairColor()
{
    if (CrossHair)
    {
        // »Ö¸´Ä¬ÈÏÑÕÉ« (ÂÌÉ«)
        CrossHair->SetColorAndOpacity(FLinearColor(0.f, 1.f, 0.f, 1.f));
    }

}
