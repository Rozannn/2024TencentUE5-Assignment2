// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT01_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual void NativeConstruct() override;


public:
	// 设置 CrossHair 的颜色
	UFUNCTION(BlueprintCallable)
	void SetCrossHairColor(FLinearColor NewColor);

	// 恢复默认颜色的接口
	UFUNCTION(BlueprintCallable)
	void ResetCrossHairColor();
	UPROPERTY(meta = (BindWidget))
	UImage* CrossHair;
};
