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
    /** 游戏剩余时间 */
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Game, meta = (AllowPrivateAccess = "true"))
    float RemainingTime;
    /** 游戏结束的回调函数 */
    void GameEnd();

    /** 同步时间到所有角色 */
    void SyncTimeToCharacters();
    void SetRandomSpecialTargets(int32 N);
    /** 用于管理游戏结束计时器的句柄 */
    FTimerHandle GameEndTimerHandle;
};



