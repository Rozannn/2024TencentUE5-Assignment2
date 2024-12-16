// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Mesh1P = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh1P"));
	Mesh1P->SetupAttachment(RootComponent);


	//BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	//BoxComponent->SetupAttachment(Mesh1P);
	Score = 10;
	bSpecial = false;
	WasHit = 0;
}

int ATarget::Hit(float Damage)
{
	if (WasHit == 0) {
		FVector Scale = GetActorScale3D();
		Scale = Scale * Damage;
		SetActorScale3D(Scale);
		WasHit = 1;
	}else if (WasHit == 1) {
		Destroy();
	}
	if (bSpecial) {
		return 2 * Score;
	}
	return Score;
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

