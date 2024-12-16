// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Assignment01GameMode.generated.h"

UCLASS(minimalapi)
class AAssignment01GameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	AAssignment01GameMode();

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Game)
    int32 SpecialNum;



protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaSeconds) override;
private:
    /** ��Ϸʣ��ʱ�� */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = "true"))
    float RemainingTime;
    /** ��Ϸ�����Ļص����� */
    void GameEnd();

    /** ͬ��ʱ�䵽���н�ɫ */
    void SyncTimeToCharacters();
    void SetRandomSpecialTargets(int32 N);
    /** ���ڹ�����Ϸ������ʱ���ľ�� */
    FTimerHandle GameEndTimerHandle;
};



