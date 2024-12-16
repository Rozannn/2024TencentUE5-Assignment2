// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "StartGameMode.generated.h"

/**
 * 
 */
UCLASS()
class ASSIGNMENT01_API AStartGameMode : public AGameMode
{
	GENERATED_BODY()
	AStartGameMode();

	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> MainMenuClass;
};
