// Copyright Epic Games, Inc. All Rights Reserved.

#include "Assignment01GameMode.h"
#include "Assignment01Character.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "Target.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AAssignment01GameMode::AAssignment01GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	RemainingTime = 20.0f;
	PrimaryActorTick.bCanEverTick = true;
	SpecialNum = 10;
}

void AAssignment01GameMode::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetFirstPlayerController()->SetShowMouseCursor(false); // ��ʾ���
	// ������Ϸ�߼�
	float T = RemainingTime;
	GetWorldTimerManager().SetTimer(GameEndTimerHandle, this, &AAssignment01GameMode::GameEnd, T, false);
	SetRandomSpecialTargets(SpecialNum);

}

void AAssignment01GameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// ����ʣ��ʱ��
	RemainingTime -= DeltaSeconds;

	// ��ֹʱ��С��0
	if (RemainingTime < 0.0f)
	{
		RemainingTime = 0.0f;
	}

	// ͬ��ʣ��ʱ�䵽��ɫ
	SyncTimeToCharacters();
}

void AAssignment01GameMode::GameEnd()
{
	// FString::Printf ��ʽ���ַ���
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Game Over! Calculating scores...")));

	int TotalScore = 0;
	TArray<AActor*> Players;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAssignment01Character::StaticClass(), Players);
	for (AActor* Actor : Players)
	{
		AAssignment01Character* Player = Cast<AAssignment01Character>(Actor);
		if (Player)
		{
			int PlayerScore = Player->GetScore(); // ����GetScore()��һ����ȡ�����ĺ���
			TotalScore += PlayerScore;

			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Player: %d, Score: %d"), Player->GetUniqueID(), PlayerScore));
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("Total Score: %d"), TotalScore));
	UGameplayStatics::SetGamePaused(GetWorld(), true);


}

void AAssignment01GameMode::SyncTimeToCharacters()
{
	TArray<AActor*> PlayerCharacters;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAssignment01Character::StaticClass(), PlayerCharacters);

	for (AActor* Actor : PlayerCharacters)
	{
		AAssignment01Character* Player = Cast<AAssignment01Character>(Actor);
		if (Player)
		{
			Player->SetTime(RemainingTime); // ���½�ɫ��ʱ��
		}
	}
}

void AAssignment01GameMode::SetRandomSpecialTargets(int32 N)
{
	TArray<AActor*> Targets;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATarget::StaticClass(), Targets);

	// ����Ƿ����㹻��ʵ��
	if (Targets.Num() < N)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough targets to set Special for %d instances"), N);
		return;
	}

	// ����һ�������б��������
	TArray<int32> Indices;
	for (int32 i = 0; i < Targets.Num(); i++)
	{
		Indices.Add(i);
	}
	Indices.Sort([](int32 A, int32 B) { return FMath::RandRange(0, 1) == 0; });

	// ���ѡ�� N ��ʵ��
	for (int32 i = 0; i < N; i++)
	{
		ATarget* Target = Cast<ATarget>(Targets[Indices[i]]);
		if (Target)
		{
			Target->bSpecial = true; // �� Special ����Ϊ 1
		}
	}
}
